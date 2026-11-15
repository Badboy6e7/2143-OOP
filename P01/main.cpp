
#include "poker.hpp"
#include <iostream>
#include <random>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;

int main(int argc, char **argv)
{
    Deck deck;
    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    deck.shuffle();

    Hand hand;
    int selected = 0;

    vector<bool> replace(5, false);

    bool drawComplete = false;

    for (int i = 0; i < 5; i++)
    {
        hand.addCard(deck.deal());
    }

    hand.sortHand();

    auto renderer = ftxui::Renderer([&]
    {
        ftxui::Elements cards;

        for (int i = 0; i < hand.size(); i++)
        {
            const Card& card = hand.getCard(i);

            string rank = rankName.at(card.getRank() + 2);
            string suit = suitName.at(card.getSuit());

            auto visualCard = ftxui::vbox(
            {
                ftxui::text(rank),
                ftxui::text(" "),
                ftxui::text(suit)
            });

            if (!drawComplete && i == selected)
            {
                cards.push_back(visualCard | ftxui::borderDouble);
            }
            else if (replace[i] && !drawComplete)
            {
                cards.push_back(
                    visualCard |
                    ftxui::color(ftxui::Color::Red) |
                    ftxui::border
                );
            }
            else
            {
                cards.push_back(visualCard | ftxui::border);
            }
        }

        return ftxui::vbox(
        {
            ftxui::text("FIVE-CARD DRAW POKER") | ftxui::bold | ftxui::center,

            ftxui::text(
                drawComplete ? "Your final hand:" : "Select cards to replace:"
            ) | ftxui::center,

            ftxui::hbox(cards) | ftxui::center,

            ftxui::text(
                drawComplete
                ? "Press Enter or Q to exit"
                : "Arrow keys: Move | Space: Select | Enter: Confirm"
            ) | ftxui::center

        }) | ftxui::border;
    });

    // Handle keyboard input.
    auto app = ftxui::CatchEvent(renderer, [&](ftxui::Event event)
    {
        // Once the final hand is displayed, allow the player to exit.
        if (drawComplete)
        {
            if (event == ftxui::Event::Return ||
                event == ftxui::Event::Character('q') ||
                event == ftxui::Event::Character('Q'))
            {
                screen.ExitLoopClosure()();
                return true;
            }

            return false;
        }

        // Move selection to the left when the left arrow key is pressed.
        if (event == ftxui::Event::ArrowLeft)
        {
            selected = (selected + 4) % 5;
            return true;
        }

        // Move selection to the right when the right arrow key is pressed.
        if (event == ftxui::Event::ArrowRight)
        {
            selected = (selected + 1) % 5;
            return true;
        }

        // Toggle replacement selection when Space is pressed.
        if (event == ftxui::Event::Character(' '))
        {
            replace[selected] = !replace[selected];
            return true;
        }

        // Replace selected cards when Enter is pressed.
        if (event == ftxui::Event::Return)
        {
            for (int i = 0; i < 5; i++)
            {
                if (replace[i])
                {
                    hand.replaceCard(i, deck.deal());
                }
            }

            hand.sortHand();

            // Clear replacement selections.
            for (int i = 0; i < 5; i++)
            {
                replace[i] = false;
            }

            drawComplete = true;

            return true;
        }

        return false;
    });

    screen.Loop(app);

    return 0;
}


