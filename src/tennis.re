/* Types */
type player =
  | PlayerOne
  | PlayerTwo;

type point = int; /* surely not the best choice */

type pointsData = {
  playerOne: point,
  playerTwo: point,
};

type score =
  /* surely incomplete */
  | Points(pointsData)
  | Deuce
  | Advantage(player)
  | Game(player);

let string_of_player =
  fun
  | PlayerOne => "Player 1"
  | PlayerTwo => "Player 2";

/* Type transformation functions */
let string_of_score: score => string =
  fun
  | Deuce => "Deuce"
  | Game(p) => "Game " ++ string_of_player(p)
  | Advantage(p) => "Advantage " ++ string_of_player(p)
  | Points({playerOne, playerTwo}) => {j|Player 1: $playerOne, Player 2: $playerTwo|j};

/* Tooling functions */
let other_player =
  fun
  | PlayerOne => PlayerTwo
  | PlayerTwo => PlayerOne;

let increment_point: point => option(point) =
  fun
  | p when p == 40 => None
  | p when p == 30 => Some(40)
  | p => Some(p + 15);

let read_from_option_point: option(point) => point =
  fun
  | Some(a) => a
  | None => 0;

/* Score management functions */

let score_when_deuce: player => score = p => Advantage(p);

let score_when_advantage: (player, player) => score =
  (advantagePlayer, winner) =>
    switch (advantagePlayer == winner) {
    | true => Game(winner)
    | _ => Deuce
    };

let score_when_forty: (player, player) => score =
  (current, winner) =>
    switch (current == winner) {
    | true => Game(winner)
    | _ => Deuce
    };

let score_when_game: player => score = winner => Game(winner);

let score: (score, player) => score =
  (currentScore, winner) =>
    switch (currentScore) {
    | Deuce => score_when_deuce(winner)
    | Advantage(current) => score_when_advantage(current, winner)
    | Points({playerOne, playerTwo}) =>
      Points(
        switch (winner == PlayerTwo) {
        | true => {
            playerOne,
            playerTwo: playerTwo |> increment_point |> read_from_option_point,
          }
        | _ => {
            playerTwo,
            playerOne: playerOne |> increment_point |> read_from_option_point,
          }
        },
      )
    };
