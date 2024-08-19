// A função é chamada quando o formulário é enviado
function handleSubmit(event) {
    event.preventDefault(); // Impede que o formulário seja enviado normalmente

    // Captura os valores dos campos
    const despesasFixas = parseFloat(document.getElementById('despesas').value.replace('R$ ', '').replace(',', ''));
    const despesasMes = parseFloat(document.getElementById('despesa_mes').value.replace('R$ ', '').replace(',', ''));
    const gastosLazer = parseFloat(document.getElementById('lazer').value.replace('R$ ', '').replace(',', ''));

    // Aqui, você pode fazer o que quiser com os valores, por exemplo, somá-los
    const totalDespesas = despesasFixas + despesasMes + gastosLazer;

    // Exiba o resultado em algum lugar, como no console ou em uma div
    console.log('Total de despesas: R$ ' + totalDespesas);
}

// Adicione um ouvinte de evento para o formulário
const form = document.querySelector('form');
form.addEventListener('submit', handleSubmit);


fetch('https://jsonserver-proknow.bernardokartabi.repl.co/usuarios')
  .then(response => {
    // Verifique se a resposta da solicitação foi bem-sucedida
    if (!response.ok) {
      throw new Error('Erro na solicitação: ' + response.status);
    }

    // Parse a resposta em formato JSON
    return response.json();
  })
  .then(data => {
    // Faça algo com os dados recuperados
    console.log(data);

    let ValorTotal = data.usuarios

  })