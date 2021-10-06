//https://contest.yandex.ru/contest/29396/problems/

#include "funcs.h"
#include <bits/stdc++.h>

enum EventType : short int{
    LineStart = 0,
    LineEnd = 1
};

struct Line{
    int numberOfSegments = 0, left, right;
    Line(int left, int right) : left(left), right(right){}
};

void parseInput(std::istream & input,
                 std::vector<std::tuple<int, EventType, int> > & events,
                 std::vector<Line> & lines,
                 int & M){
    input>>M;

    int left, right;
    input>>left>>right;
    int i = 0;
    while (!(left == 0 && right == 0)){
        if(left<M && right>0){
            lines.emplace_back(left, right);
            events.emplace_back(left,LineStart,i);
            events.emplace_back(right,LineEnd,i);
            ++i;
        }
        input>>left>>right;
    }
}

void parseFile(std::istream & input, std::ostream & output){
    //! position, type, index of line
    std::vector<std::tuple<int, EventType, int> > events;
    std::vector<Line> lines;
    int M;
    parseInput(input,events,lines, M);

    std::sort(events.begin(), events.end());

    if(events.empty() || std::get<0>(events[0]) > 0 || std::get<0>(events.back()) < M){
        output<<"No solution"<<std::endl;
        return;
    }

    std::unordered_set<int> currentLines;
    std::unordered_set<int> usedLines;
    bool noAnswer = false;
    for(int i = 0; i<events.size(); ++i){
        auto [pos, type, lineIndex] = events[i];

        if(i == 0 ||
            std::get<0>(events[i-1]) != pos){
            //before all events at pos
            if(pos > 0) {

                for(auto j: currentLines){
                    ++lines[j].numberOfSegments;
                }

                if(pos <= M){
                    if(currentLines.empty()){
                        noAnswer = true;
                        break;
                    } else if(currentLines.size() == 1){
                        usedLines.insert(*currentLines.begin());
                    }
                }
            }
        }

        switch (type) {
            case LineStart:
                currentLines.insert(lineIndex);
                break;
            case LineEnd:
                currentLines.erase(lineIndex);
                break;
        }

        if( i == events.size()-1 ||
                std::get<0>(events[i+1]) != pos){
            //after all event at pos
            if(pos > 0 && pos < M && currentLines.empty()){
                noAnswer = true;
                break;
            }

            if(pos >= M){
                break;
            }
        }
    }

    if(noAnswer){
        output<<"No solution"<<std::endl;
        return;
    }

    currentLines.clear();
    for(int i = 0; i<events.size(); ++i){
        auto [pos, type, lineIndex] = events[i];
        if(i == 0 ||
           std::get<0>(events[i-1]) != pos){
            //before all events at pos
            if(pos > 0) {
                int bestNumberOfSegments = -1;
                int bestLine = -1;
                bool alreadyUsed = false;
                for(auto j: currentLines){
                    if(usedLines.count(j)){
                        alreadyUsed = true;
                        break;
                    }
                    int numberOfSegments = lines[j].numberOfSegments;
                    if(numberOfSegments > bestNumberOfSegments){
                        bestLine = j;
                        bestNumberOfSegments = numberOfSegments;
                    }
                }
                if(!alreadyUsed){
                    usedLines.insert(bestLine);
                }
            }
        }

        switch (type) {
            case LineStart:
                currentLines.insert(lineIndex);
                break;
            case LineEnd:
                currentLines.erase(lineIndex);
                break;
        }

        if(pos >= M){
            break;
        }
    }

    //print answer
    output<<usedLines.size()<<'\n';
    std::vector<std::pair<int,int>> lineCoordinates;
    lineCoordinates.reserve(usedLines.size());
    for(auto & i : usedLines){
        lineCoordinates.emplace_back(lines[i].left, lines[i].right);
    }
    std::sort(lineCoordinates.begin(),lineCoordinates.end());
    for(auto & line : lineCoordinates){
        output<<line.first<<' '<<line.second<<'\n';
    }
}
