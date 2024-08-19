
//const apiPath = "https://jsonserver-proknow.joopaulopaulo33.repl.co/usuarios";

(() => {
    'use strict'
    const forms = document.querySelectorAll('.needs-validation')

    Array.from(forms).forEach(form => {
        form.addEventListener('submit', event => {
            if (!form.checkValidity()) {
                event.preventDefault()
                event.stopPropagation
            }

            form.classList.add('was-validated')
        }, false)
    })
})()

function displayMessage(message){
    message =   document.getElementById('msg');
    message = `<div class="alert alert-warning"> ${message} <\div>`
}

function registerIncomings(processaDados) {
    fetch(apiPath)
    .then(response => response.json)
    .then(data => {
       processaDados(data);
    })
    .catch(error => {
        console.error('Deu ruim paizão');
        
    })
}


function createIncoming(user, resfresh){
    fetch(apiPath, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(user),
    })
    .then(response => response.json())
    .then(data => {
        displayMessage('Ganho cadastrado');
        if(resfresh){
            resfreshFunction();
        }   
    })
    .catch(error => {
        console.error("Erro ao atualizar contato");
        displayMessage("Erro ao atualizar")
    })
}









