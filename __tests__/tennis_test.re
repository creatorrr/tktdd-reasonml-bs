open Jest;

open Expect;

open Tennis;

describe("Test Tooling", () =>
  test("Given a Player 1 the other player is Player 2", () =>
    expect(other_player(PlayerOne) |> string_of_player)
    |> toEqual("Player 2")
  )
);

describe("Test Game transitions", () => {
  test("Given deuce when player wins then score is correct", () =>
    expect(score_when_deuce(PlayerOne) |> string_of_score)
    |> toEqual("Advantage Player 1")
  );
  test(
    "Given advantage when advantaged player wins then score is Game to the advantaged player",
    () => {
      let advantagedPlayer = PlayerOne;
      let winner = advantagedPlayer;
      expect(
        score_when_advantage(advantagedPlayer, winner) |> string_of_score,
      )
      |> toEqual("Game Player 1");
    },
  );
  test("Given advantage when the other player wins then score is Deuce", () => {
    let advantagedPlayer = PlayerOne;
    let winner = other_player(advantagedPlayer);
    expect(score_when_advantage(advantagedPlayer, winner) |> string_of_score)
    |> toEqual("Deuce");
  });
  /* Tests bellow need more conception on types to be implemented */
  test(
    "Given player: 40 when player at 40 wins then score is Game for this player",
    () => {
    let p = PlayerOne;
    expect(score_when_forty(p, p) |> string_of_score)
    |> toEqual("Game Player 1");
  });
  test("Given player: 40 | other : 30 when other wins then score is Deuce", () => {
    let p1 = PlayerOne;
    let p2 = other_player(p1);
    expect(score_when_forty(p1, p2) |> string_of_score) |> toEqual("Deuce");
  });
  test("Given player: 40 | other : 15 when other wins then score is 40/30", () => {
    let currentScore = Points({playerOne: 40, playerTwo: 15});
    let output = "Player 1: 40, Player 2: 30";
    expect(score(currentScore, PlayerTwo) |> string_of_score)
    |> toEqual(output);
  });
  test(
    "Given player: 15 | other : 15 when player wins then score is 30/15", () => {
    let currentScore = Points({playerOne: 15, playerTwo: 15});
    let output = "Player 1: 30, Player 2: 15";
    expect(score(currentScore, PlayerOne) |> string_of_score)
    |> toEqual(output);
  });
  test("Given player: 0 | other : 15 when other wins then score is 0/30", () => {
    let currentScore = Points({playerOne: 0, playerTwo: 15});
    let output = "Player 1: 0, Player 2: 30";
    expect(score(currentScore, PlayerTwo) |> string_of_score)
    |> toEqual(output);
  });
  test(
    "Given player: 30 | other : 15 when player wins then score is 40/15", () => {
    let currentScore = Points({playerOne: 30, playerTwo: 15});
    let output = "Player 1: 40, Player 2: 15";
    expect(score(currentScore, PlayerOne) |> string_of_score)
    |> toEqual(output);
  });
});
