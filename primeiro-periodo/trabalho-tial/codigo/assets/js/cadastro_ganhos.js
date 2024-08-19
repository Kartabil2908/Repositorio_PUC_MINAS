const apiPath = 'https://jsonserver-proknow.joopaulopaulo33.repl.co/usuarios';


async function readUsers() {

  await fetch(apiPath)
    .then(response => response.json())
    .then(users => {
      console.log(users);
    })
    .catch(error => {
      console.error('Erro ao ler usuarios', error);
      displayMessage("Deu ruim ae paizão");
    })

}



function registerIncoming(obj) {

  fetch(apiPath, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(jsonBody + obj)
  })

    .then(response => {
      response.json();
      console.log(response.json())
    })
    .then(data => {
      console.log('Success:');
      console.log(data);
    })
    .catch(error => {
      console.error('Erro ao inserir contato via API', error);

    })
}













