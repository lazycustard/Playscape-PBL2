document.getElementById('add-username-btn').addEventListener('click', function() {
    document.getElementById('welcome-screen').style.display = 'none';
    document.getElementById('username-input-screen').style.display = 'block';
});

function startGame() {
    let username = document.getElementById('username').value.trim();
    if (username !== '') {
        document.getElementById('username-input-screen').style.display = 'none';
        document.getElementById('game-selection-screen').style.display = 'block';
    } else {
        alert('Please enter a username');
    }
}

document.getElementById('start-btn').addEventListener('click', startGame);

document.getElementById('username').addEventListener('keypress', function(event) {
    if (event.key === "Enter") {
        startGame();
    }
});

const games = {
    'number_guessing': 'number_guessing.exe',
    'snake': 'snake.exe',
    'sudoku': 'sudoku.exe',
    'word_scramble': 'xo.exe',
    'word_maze': 'tictactoe.exe',
    'typingspeed' : 'typing_speed.exe',
};

document.querySelectorAll('.game-box').forEach(box => {
    box.addEventListener('click', function() {
        let game = this.getAttribute('data-game');
        console.log(game);  
        if (game in games) {
            window.location.href = games[game];
        } else {
            alert('Game not found');
        }
    });
});



