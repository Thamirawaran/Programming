"""A Rock, Paper, Scissors Game"""

import:py random;

"""
This game is written based on number guessing game given on jac platform
"""
obj Game {
    can init(attempts: int) {
        self.attempts = attempts;
        }

    can play() {
        raise NotImplementedError(
            "Subclasses must implement this method."
        );
    }
}

"""
A rock, paper, scissors game where the player competes against the computer.
"""
obj RockPaperScissors :Game: {
    can init(attempts: int=10) {
        super.init(attempts);
        self.choices = ["rock", "paper", "scissors"];
        self.computer_win =0;
        self.player_win = 0;
    }

    can play() {
        print("Welcome to Rock, Paper, Scissors!");

        while self.attempts > 0 {
            player_choice = input("Choose rock, paper, or scissors (or type 'quit' to end): ").lower();
            if player_choice == "quit" {
                print("Thanks for playing!");
                break;
            }
            if not player_choice in self.choices {
                print("Invalid choice. Try again.");
                continue;
            }

            computer_choice = random.choice(self.choices);
            self.process_choice(player_choice, computer_choice);
        }

        print("Game over! Thanks for playing.");
    }

    can process_choice(player_choice: str, computer_choice: str) {
        print(f"Computer chose: {computer_choice}");

        if player_choice == computer_choice {
            print("It's a tie!");
        } elif (player_choice == "rock" and computer_choice == "scissors") or 
              (player_choice == "scissors" and computer_choice == "paper") or 
              (player_choice == "paper" and computer_choice == "rock") {
            self.player_win += 1;  # Increment player win count
            print(f"You win! {self.player_win} times");
        } else {
            self.computer_win += 1;  # Increment computer win count
            print(f"Computer wins! {self.computer_win} times");
        }

        self.attempts -= 1;
        print(f"You have {self.attempts} rounds left.");
    }
}

# Run the game
"""
Object instantiation and method invocation occur within the with entry { ... } block.
"""
with entry {
    game = RockPaperScissors();
    game.play();
}
