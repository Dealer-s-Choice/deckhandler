/*
 * deckhandler.c
 * Library to handle a deck of cards
 * <https://github.com/theimpossibleastronaut/deckhandler>
 *

 MIT License

 Copyright (c) 2019-2025 Andy Alt

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*/

#include <pcg_basic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "deckhandler.h"

static pcg32_random_t rng;

static const char *suits[] = {"Hearts  ", "Diamonds", "Spades  ", "Clubs   "};

static const char *faces[] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                                 "8",   "9", "10", "Jack", "Queen", "King"};

const DH_Card DH_card_back = {
    .face_val = DH_CARD_BACK,
    .suit = DH_CARD_BACK,
};

const DH_Card DH_card_null = {
    .face_val = DH_CARD_NULL,
    .suit = DH_CARD_NULL,
};

bool DH_is_card_back(DH_Card a) {
  return a.face_val == DH_CARD_BACK && a.suit == DH_CARD_BACK;
}

bool DH_is_card_null(DH_Card a) {
  return a.face_val == DH_CARD_NULL && a.suit == DH_CARD_NULL;
}

void DH_pcg_srand(uint64_t initstate, uint64_t initseq) {
  pcg32_srandom_r(&rng, initstate, initseq);
  return;
}

void DH_pcg_srand_auto(void) {
  uint64_t initstate = time(NULL) ^ (intptr_t)&printf;
  uint64_t initseq = (intptr_t)&faces;
  pcg32_srandom_r(&rng, initstate, initseq);
}

static void DH_init_deck(DH_Deck *deck) {
  deck->top_card = 0;

  int card = 0;
  int suit = 0;
  int face = DH_CARD_ACE;

  while (suit < DH_SUIT_MAX) {
    deck->card[card].face_val = face++;
    deck->card[card].suit = suit;

    if (face > DH_CARD_KING) {
      face = DH_CARD_ACE;
      suit++;
    }

    card++;
  }
  return;
}

DH_Deck DH_get_new_deck(void) {
  DH_Deck deck;
  DH_init_deck(&deck);
  return deck;
}

DH_Card DH_deal_top_card(DH_Deck *deck) {
  if (deck->top_card == DH_CARDS_IN_DECK) {
    deck->top_card = 0;
    puts("deckhandler: deck wrapped");
  }
  DH_Card card = deck->card[deck->top_card];
  deck->top_card++;
  return card;
}

static void swap(DH_Deck *deck_dh, int i, int j) {
  DH_Card tmp = deck_dh->card[i];
  deck_dh->card[i] = deck_dh->card[j];
  deck_dh->card[j] = tmp;
}

void DH_shuffle_deck(DH_Deck *deck) {
  for (int i = DH_CARDS_IN_DECK - 1; i > 0; --i) {
    int j = pcg32_boundedrand_r(&rng, i + 1);
    swap(deck, i, j);
  }
  deck->top_card = 0;
}

void DH_cut_deck(DH_Deck *deck, const int cut_point) {
  if (cut_point <= 0 || cut_point >= DH_CARDS_IN_DECK)
    return; // No cut if point is out of bounds

  DH_Card temp[DH_CARDS_IN_DECK];
  int i, j = 0;

  // Copy bottom half first
  for (i = cut_point; i < DH_CARDS_IN_DECK; ++i)
    temp[j++] = deck->card[i];

  // Then copy top half
  for (i = 0; i < cut_point; ++i)
    temp[j++] = deck->card[i];

  // Copy back to original deck
  memcpy(deck->card, temp, sizeof(temp));
}

const char *DH_get_card_face(DH_Card card) { return faces[card.face_val - 1]; }

const char *DH_get_card_suit(DH_Card card) { return suits[card.suit]; }

static const char *const DH_suit_unicode[] = {
    [DH_SUIT_DIAMONDS] = "\u2666",
    [DH_SUIT_HEARTS]   = "\u2665",
    [DH_SUIT_SPADES]   = "\u2660",
    [DH_SUIT_CLUBS]    = "\u2663"
};

const char *DH_get_unicode_suit(DH_suit suit) {
    if (suit >= 0 && suit <= DH_SUIT_CLUBS)
        return DH_suit_unicode[suit];
    return "?";
}

const char *DH_get_card_unicode_suit(DH_Card card) {
    return DH_get_unicode_suit(card.suit);
}

const char *DH_get_card_face_str(int val) {
  switch (val) {
  case 1:
    return "A";
  case 11:
    return "J";
  case 12:
    return "Q";
  case 13:
    return "K";
  default: {
    static char buf[3];
    snprintf(buf, sizeof(buf), "%d", val);
    return buf;
  }
  }
}
