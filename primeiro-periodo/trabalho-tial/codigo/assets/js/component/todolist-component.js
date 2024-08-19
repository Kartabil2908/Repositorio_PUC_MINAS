const apiPath = 'https://jsonserver-proknow.joopaulopaulo33.repl.co/usuarios';


function registerTask(task) {
    fetch(apiPath, {
        method: 'POST',
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(task)
    })
        .then(response => response.json())
        .then(data => {
            console.log('Success:', data);
            console.log('Sucesso ao registrar task');
        })
        .catch(error => console.error('Erro ao cadastrar tarefa', error))
}

function deleteTask(id) {
    fetch(apiPath + 'id', {
        method: 'DELETE',
    })
        .then(response => response.json())
        .then(data => {
            console.log('task deletada', data);
        })
        .catch(error => {
            console.error('erro ao deletar task', error);
        })
}