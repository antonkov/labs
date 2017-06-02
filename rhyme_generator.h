#pragma once

#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

typedef vector<string> vs;

struct rhyme_generator_t {
    vs words;

    vs genRandomLine(int lenTarget) { // Генерирует рандомную строку длины чуть большую lenTarget
        int len = 0;
        vs s;
        while (len < lenTarget) {
            string word = words[rand() % words.size()];
            s.push_back(word);
            len += word.length() + 1;
        }
        return s;
    }

    pair<vs, vs> genRandom() { // Генериует пару рифмующихся строк
        int lenTarget = 50;
        vs first = genRandomLine(lenTarget);
        vs second = genRandomLine(lenTarget);
        return make_pair(first, second);
    };

    vector<pair<string, string> > rhymes; // Строфа в рифму

    double penalty(pair<vs, vs> &s) { // Начисляем штрафы
        string l1 = s.first.back();
        string l2 = s.second.back();
        if (l1 > l2)
            swap(l1, l2); // Нельзя считать рифмой перевернутую рифму, сгенерированную раньше
        double val = 0;
        for (auto rhyme : rhymes) {
            if (l1 == rhyme.first && l2 == rhyme.second) { // Штраф 45 если рифма была раньше
                val += 45;
            }
        }
        if (l1 == l2) {
            val += 100; // Начисляе штраф 100 если слова одинаковы
        } else {
            int cnt = 0;
            while (l1.length() > cnt && l2.length() > cnt
                   && l1[l1.length() - 1 - cnt] == l2[l2.length() - 1 - cnt])
                cnt++;
            val += 50 - 10 * cnt; //Начисляем штраф 50 если слова полностью различны
        }
        vs ws;
        int lenFirst = 0;
        int lenSecond = 0;
        for (string ss : s.first) {
            ws.push_back(ss);
            lenFirst += ss.length() + 1;
        }
        for (string ss : s.second) {
            ws.push_back(ss);
            lenSecond += ss.length() + 1;
        }
        val += 1 * abs(lenFirst - lenSecond);
        for (int i = 0; i < ws.size(); i++) {
            int x = 0;
            for (int j = i; j < ws.size(); j++) {
                if (ws[i] == ws[j]) {
                    x++;
                }
            }
            val += x * x; // Штраф за повторение слова в рифме
        }

        return val;
    }

    pair<vs, vs> genRhyme() {
        int CNT_ITER = 10 * 1000;
        pair<vs, vs> ans;
        double ansVal = 1e9;
        for (int iter = 0; iter < CNT_ITER; iter++) {
            pair<vs, vs> cur = genRandom(); // Генерируем рандомные рифмы
            double val = penalty(cur);
            if (val < ansVal) {
                ansVal = val;
                ans = cur; // Выбираем рифму с меньшим штрафом
            }
        }
        string l1 = ans.first.back();
        string l2 = ans.second.back();
        if (l1 > l2)
            swap(l1, l2);
        rhymes.push_back(make_pair(l1, l2));

        return ans;
    }
};

