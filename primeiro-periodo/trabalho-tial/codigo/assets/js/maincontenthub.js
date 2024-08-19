document.addEventListener("DOMContentLoaded", function() {
    // Votação
    let voteButtons = document.querySelectorAll(".vote-button, .vote-minus");
    voteButtons.forEach(button => {
        button.addEventListener("click", function() {
            let counter = this.parentElement.querySelector(".vote-count b");
            let count = parseInt(counter.textContent, 10);
            if (this.classList.contains("vote-button")) {
                count++;
            } else {
                count--;
            }
            counter.textContent = count;
        });
    });

    // Barra de pesquisa
    let searchInput = document.getElementById("search");
    searchInput.addEventListener("keyup", function() {
        let filter = searchInput.value.toLowerCase();
        let items = document.querySelectorAll(".start .item");
        items.forEach(item => {
            let text = item.querySelector("h7").textContent.toLowerCase();
            if (text.indexOf(filter) > -1) {
                item.style.display = "";
            } else {
                item.style.display = "none";
            }
        });
    });
});

// script.js
var commentInput = document.querySelector('.comment-input textarea');
var charCount = document.querySelector('.char-count');

commentInput.addEventListener('input', function() {
  var count = commentInput.value.length;
  charCount.textContent = count + '/200';
});


