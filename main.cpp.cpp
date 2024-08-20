#include <iostream>

using namespace std;

int main() {
    long long codigo;
    cout << "Digite o código de barras (13 dígitos): ";
    cin >> codigo;

// Aqui utilizamos if para verificar se o código tem exatamente 13 dígitos; caso não tenha, retornamos o valor 1, que indica erro. Usamos LL para garantir que ambos os literais numéricos sejam tratados como long long.
    if (codigo < 1000000000000LL || codigo > 9999999999999LL) {
        cout << "Número de dígitos inválido. Deve conter exatamente 13 dígitos." << endl;
        return 1;
    }

// Aqui salvamos em 'temp' os 12 primeiros dígitos, descartando o último, já que a operação / 10 pega somente valores inteiros. Em 'digito_verificador_real', salvamos o último número, que é o dígito verificador, através da operação de módulo, pegando o resto da divisão dos 13 dígitos por 10.
    long long temp = codigo / 10;
    int digito_verificador_real = codigo % 10;

// A variável 'soma' inicia com valor 0 (vazio), porém vamos adicionando dentro dela os novos valores dos 12 primeiros dígitos após resolvermos suas operações, que são o mesmo valor para números nas posições pares e multiplicação por 3 nos valores das posições ímpares.
// Aqui iniciamos um loop for; 'i' indica quantas vezes o loop será executado, nesse caso 12 vezes, pois queremos pegar os 12 primeiros dígitos para fazer as suas respectivas operações. Os valores das posições pares permanecem os mesmos, e os que estão nas posições ímpares são multiplicados por 3.
// Nesse caso, 'i' também é responsável por nos indicar qual posição estamos "pegando", começando pela posição 1 (ímpar) e depois 2 (par) e assim sucessivamente.
// A variável 'digito' serve para separarmos o último dígito dos 12 primeiros que estava armazenado dentro de 'temp'; fazemos isso usando o módulo da divisão de 10.
// Depois fazemos as verificações de par e ímpar para as posições dos 12 primeiros dígitos, usando o if (i % 2 == 0), que nesse caso indica que o valor de 'i' seja 1 na primeira execução do loop. Ele compara a posição 1 na divisão por 2 e verifica se o restante da operação é 0, o que indicaria que o valor é par; caso não seja, ele já identifica que é ímpar.
// Se for par, ele já adiciona o valor dentro da variável 'soma' que iniciou o loop com 0 (vazio) utilizando soma += dígito. Ou seja, se a posição 2, que é par, contém o número hipotético 8, ele adiciona o valor 8 diretamente dentro da variável 'soma' que estava vazia. Isso é feito para obtermos os novos 12 primeiros dígitos após passarem por suas respectivas operações.
// Já se for ímpar, primeiro multiplicamos por 3 e logo após também armazenamos dentro da variável 'soma', soma += digito * 3.
// Ao final de cada repetição do loop, usamos temp /= 10 para garantir que não vamos realizar o loop novamente na mesma posição e valor, pois com essa operação removemos o último número que estava em 'temp'. A lógica aqui é realizar as operações número por número da direita para a esquerda, começando pela posição 12, que representaria a "casa" 1 (ímpar), pois o código de barras EAN-13 inicia da esquerda para a direita, onde o 12 (par) seria o primeiro número do código da esquerda para a direita.
    int soma = 0;

    for (int i = 1; i <= 12; ++i) {
        int digito = temp % 10;

        if (i % 2 == 0) {
            soma += digito;
        } else {
            soma += digito * 3;
        }

        temp /= 10;
    }

// Aqui armazenamos dentro da variável 'proximo_multiplo_10' o valor de 'soma' mais 9 para garantir que o resultado sempre chegue no próximo múltiplo de 10, seguindo com a divisão por 10 * 10. Ou seja, supondo que o resultado de 'soma' seja 17, se seguíssemos as regras de execução do EAN-13 de dividir por 10 e logo após multiplicar por 10, ficaria assim: 17 / 10 * 10. Ou seja, 17 dividido por 10 dá o quociente 1; depois multiplicamos por 10, seguindo a ordem de operação aritmética da esquerda para a direita, 1 * 10 = 10, o que estaria errado, já que o valor 10 seria inferior ao próximo múltiplo de 10 de 17, que é 20. Então colocamos o 9, que sempre funcionará para essa situação, ficando (soma + 9) / 10 * 10. 17 + 9 = 26 / 10 dá o quociente 2; 2 * 10 = 20. Depois pegamos o 20 e subtraímos o valor de 'soma' dele, ficando 20 - 17 = 3, que é o nosso dígito verificador.
// Logo após, dentro do if, realizamos a verificação se o resultado de 'digito_verificador_calculado' é exatamente igual ao digitado pelo usuário em 'digito_verificador_real'. Se essa informação estiver correta, retornamos a mensagem "Código de barras correto." ao usuário; porém, se a informação não for validada, ou seja, se os dígitos verificadores dentro das variáveis não coincidirem, será retornada ao usuário a mensagem "Dígito verificador inconsistente.".
// Depois fazemos um if para garantir que o dígito verificador seja único. Ou seja, se ele for, por exemplo, 10, que é o único múltiplo de 10 que o algoritmo do EAN-13 permite, nós o convertemos em 0, garantindo que o código de barras tenha exatamente 13 dígitos e um dígito verificador único.
// Finalmente, usamos return 0 para indicar que o programa foi executado corretamente.
    int proximo_multiplo_10 = (soma + 9) / 10 * 10;
    int digito_verificador_calculado = proximo_multiplo_10 - soma;
    
    if (digito_verificador_calculado == 10) {
        digito_verificador_calculado = 0;
    }

    if (digito_verificador_calculado == digito_verificador_real) {
        cout << "Código de barras correto." << endl;
    } else {
        cout << "Dígito verificador inconsistente." << endl;
    }

    return 0;
}
