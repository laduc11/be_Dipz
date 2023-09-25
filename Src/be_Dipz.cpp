#include "../Inc/main.h"
/*
choose index
output: 20 vị trí trong bộ dữ liệu 100 câu hỏi
*/
vector<int> choose()
{
    vector<int> select, result;
    srand(time(0));
    fstream shuffle;
    shuffle.open("./Input/shuffle.txt", ios::in);
    int idx;
    for (int i = 0; i < NUM_Q / 4; i++)
    {
        select.push_back(rand() % (TOTAL_Q / 4));
        select.push_back((rand() % (TOTAL_Q / 4)) + (TOTAL_Q / 4));
        select.push_back((rand() % (TOTAL_Q / 4)) + (TOTAL_Q / 4) * 2);
        select.push_back((rand() % (TOTAL_Q / 4)) + (TOTAL_Q / 4) * 3);
    }
    for (int i = 0; i < NUM_Q; i++)
    {
        shuffle >> idx;
        result.push_back(select[idx]);
    }
    shuffle.close();
    return result;
}
/*
initial math test
input:
    database of math
    chosen index
ouput:
    Correct or Wrong
*/
int math_test(vector<pair<string, string>> source, int i)
{
    int correct = 0;
    system("cls");
    string status;
    char answer;
    fstream result;
    result.open("./Ouput/log/result.txt", ios::app);

    cout << "Nếu biểu thức đúng gõ 't', nếu sai gõ 'f'\nSau đó bấm phím Enter\n\n\n";
    cout << source[i].first << endl;
    result << source[i].first << '\n';
    auto start = chrono::steady_clock::now();
    cin >> answer;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    if (elapsed_seconds.count() > DELAY_TIMER_Q / 1000.0)
    {
        status = "OVER TIME";
    }

    if (answer == 't')
        status = "TRUE";
    else if (answer == 'f')
        status = "FALSE";
    else
        status = "SYNTAX ERROR";

    if (status == source[i].second)
        correct++;

    if (status == "TRUE" || status == "FALSE")
        cout << source[i].second << endl;
    else
        cout << status << '\n';
    result << "Your answer: " << answer << '\n';
    result << "Solution: " << source[i].second << '\n';
    result << "Status: " << status << '\n';
    result.close();
    Sleep(DELAY_TIMER_S);

    return correct;
}

/*
vocabulary test
*/
void vocab_test(vector<string> source, int i)
{
    fstream result;
    result.open("./Ouput/participant/000.txt", ios::app);
    result << source[i] << '\n';
    result.close();

    system("cls");
    cout << "\n\n\n\t" << source[i];
    Sleep(DELAY_TIMER_Q);
    system("cls");
}

/*
get equation source
*/
vector<pair<string, string>> get_equation()
{
    vector<pair<string, string>> source;
    fstream source_equation;
    source_equation.open("./Input/equation.txt", ios::in);
    while (!source_equation.eof())
    {
        string answer, equation;
        getline(source_equation, answer, '\t');
        getline(source_equation, equation, '\n');
        source.push_back(make_pair(equation, answer));
    }
    source_equation.close();
    return source;
}
/*
get vocabulary source
*/
vector<string> get_vocab()
{
    fstream vocab_source;
    vocab_source.open("./Input/vocab.txt", ios::in);
    vector<string> source;
    while (!vocab_source.eof())
    {
        string temp;
        vocab_source >> temp;
        source.push_back(temp);
    }
    vocab_source.close();
    return source;
}
