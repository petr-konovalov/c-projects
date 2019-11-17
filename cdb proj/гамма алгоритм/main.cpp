#include <iostream>
#include <graphics.h>
#include "geometry.h"
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <ctime>

using namespace std;

struct Graph
{
    //структура графа
    vector<pair<int, int> > lines;
    vector<vector<int> > adjLine;

    //уложенный подграф
    vector<bool> takedLine;
    vector<bool> takedPoint;
    //списки граней смежных вершинам уложенного подграфа
    vector<vector<int> > adjVerg;

    //геометрия
    vector<Point> coord;
    vector<Polygon> verges;

    Graph(const int pointCount, const int lineCount)
    {
        lines.reserve(lineCount);
        takedLine.resize(lineCount);
        takedPoint.resize(pointCount);
        verges.resize(pointCount);
        coord.resize(pointCount);
        adjLine.resize(pointCount);
        adjVerg.resize(pointCount);
    }
};

struct DfsInfo
{
    vector<int> seg;
    vector<int> used;
    vector<vector<int> > contactPoint;
    vector<int> chain;
    int segCount;

    DfsInfo(const int pointCount, const int lineCount)
    {
        seg = vector<int>(lineCount, 0);
        used = vector<int>(pointCount, 0);
    }
};

const long long seed = time(0);

void drawPolyline(const Polyline poly, const int dx = 0, const int dy = 0, const double M = 20)
{
    circle((int)(poly[0].x * M) + dx, getmaxy() - (int)(poly[0].y * M) - dy, 5);
    for (int i = 1; i < poly.size(); ++i)
    {
        circle((int)(poly[i].x * M) + dx, getmaxy() - (int)(poly[i].y * M) - dy, 5);
        line((int)(poly[i - 1].x * M) + dx, getmaxy() - (int)(poly[i - 1].y * M) - dy,
             (int)(poly[i].x * M) + dx, getmaxy() - (int)(poly[i].y * M) - dy);
    }
}

void drawPoly(const Polygon poly, const int dx = 0, const int dy = 0, const double M = 20, const bool circlePoint = true)
{
    if (circlePoint)
        circle((int)(poly[0].x * M) + dx, getmaxy() - (int)(poly[0].y * M) - dy, 5);
    for (int i = 1; i < poly.size(); ++i)
    {
        if (circlePoint)
            circle((int)(poly[i].x * M) + dx, getmaxy() - (int)(poly[i].y * M) - dy, 5);
        line((int)(poly[i - 1].x * M) + dx, getmaxy() - (int)(poly[i - 1].y * M) - dy,
             (int)(poly[i].x * M) + dx, getmaxy() - (int)(poly[i].y * M) - dy);
    }
    line((int)(poly.back().x * M) + dx, getmaxy() - (int)(poly.back().y * M) - dy,
         (int)(poly[0].x * M) + dx, getmaxy() - (int)(poly[0].y * M) - dy);
}

void intToStr(int i, char *str)
{
    int len = 0;
    if (i == 0)
    {
        len = 1;
        str[0] = '0';
    }
    while (i)
    {
        int digit = i % 16;
        str[len] = digit < 10 ? '0' + digit: 'A' + digit - 10;
        i /= 16;
        ++len;
    }
    reverse(str, str + len);
    str[len] = '\0';
}

void drawNode(int id, const double x, const double y, const int dx, const int dy, const double M = 20, const int radius = 7)
{
    setcolor(RED);
    circle((int)(x * M) + dx, getmaxy() - (int)(y * M) - dy, radius);
    floodfill((int)(x * M) + dx, getmaxy() - (int)(y * M) - dy, RED);
    setcolor(BLACK);
    char value[16];
    intToStr(id, value);
    outtextxy((int)(x * M) - textwidth(value) / 2 + dx, getmaxy() - (int)(y * M) - dy - textheight(value) / 2, value);
}

void drawGraph(const Graph graph, const int dx, const int dy, const double M = 20)
{
    setcolor(BLUE);
    for (int i = 0; i < graph.verges.size(); ++i)
        drawPoly(graph.verges[i], dx, dy, M, false);
    setfillstyle(SOLID_FILL, YELLOW);
    for (int i = 0; i < graph.adjLine.size(); ++i)
        if (graph.takedPoint[i])
            drawNode(i, graph.coord[i].x, graph.coord[i].y, dx, dy, M);
}

bool getCycle(Graph &graph, vector<int> &cycle, vector<int> &used, int vertex = 0, int parent = -1)
{
    static mt19937 generator(seed);
    if (used[vertex] == 1)
    {
        cycle.push_back(vertex);
        return true;
    }
    used[vertex] = 1;
    shuffle(graph.adjLine[vertex].begin(), graph.adjLine[vertex].end(), generator);
    for (int i = 0; i < graph.adjLine[vertex].size(); ++i)
    {
        int to = graph.lines[graph.adjLine[vertex][i]].first;
        if (to == vertex)
            to = graph.lines[graph.adjLine[vertex][i]].second;
        if (used[to] != 2 && to != parent)
        {
            if (getCycle(graph, cycle, used, to, vertex))
            {
                if (cycle.front() != cycle.back() || cycle.size() == 1)
                    cycle.push_back(vertex);
                return true;
            }
        }
    }
    used[vertex] = 2;
    return false;
}

/** проверяет правильность обхода вершин выпуклого многоугольника */
bool checkOrientation(const Polygon poly)
{
    return (poly[2] - poly[1]) * (poly[0] - poly[1]) > 0;
}

/**распологает вершины цикла по окружности радиуса R*/
void layCycle(Graph &graph, const vector<int> &cycle, int R = 5)
{
    int n = cycle.size() - 1;
    double angle = M_PI * 2 / n;
    double x = -R;
    double y = 0;
    double sina = sin(angle);
    double cosa = cos(angle);
    graph.verges = vector<Polygon>(2, Polygon());
    //располагаем вершины по кругу
    for (int i = 0; i < n; ++i)
    {
        double tx = cosa * x - sina * y;
        double ty = sina * x + cosa * y;
        graph.coord[cycle[i]] = Point(x, y);
        graph.verges[0].push_back(graph.coord[cycle[i]]);
        graph.verges[1].push_back(graph.coord[cycle[i]]);
        graph.takedPoint[cycle[i]] = true;
        int next = cycle[(i + 1) % n];
        for (auto line: graph.adjLine[cycle[i]])
            if (graph.lines[line].first == next || graph.lines[line].second == next)
            {
                graph.takedLine[line] = true;
                break;
            }
        graph.adjVerg[cycle[i]].push_back(0);
        graph.adjVerg[cycle[i]].push_back(1);
        x = tx;
        y = ty;
    }
    //устанавливам правильную ориентацию вершин
    if (!checkOrientation(graph.verges[0]))
    {
        reverse(graph.verges[0].begin(), graph.verges[0].end());
        reverse(graph.verges[1].begin(), graph.verges[1].end());
    }
}

void dfsLine(const Graph graph, const int line, DfsInfo &dfsInfo);

void dfsPoint(const Graph graph, const int point, DfsInfo &dfsInfo)
{
    if (dfsInfo.used[point] != dfsInfo.contactPoint.size())
    {
        dfsInfo.used[point] = dfsInfo.contactPoint.size();
        if (graph.takedPoint[point])
            dfsInfo.contactPoint.back().push_back(point);
        else
            for (int to: graph.adjLine[point])
                dfsLine(graph, to, dfsInfo);
    }
}

void dfsLine(const Graph graph, const int line, DfsInfo &dfsInfo)
{
    if (dfsInfo.seg[line] == 0)
    {
        dfsInfo.seg[line] = dfsInfo.contactPoint.size();
        dfsPoint(graph, graph.lines[line].first, dfsInfo);
        dfsPoint(graph, graph.lines[line].second, dfsInfo);
    }
}

pair<int, int> getMinSeg(const Graph graph, const DfsInfo dfsInfo)
{
    const int INF = 1000000000;
    int minVergSeg = 0;
    int minVergCnt = INF;
    int resVerg = 0;
    vector<int> pointTouchVerg(graph.verges.size());
    for (int i = 0; i < dfsInfo.contactPoint.size(); ++i)
    {
        int curVergCnt = 0;
        int curVerg = 0;
        fill(pointTouchVerg.begin(), pointTouchVerg.end(), 0);
        for (int point: dfsInfo.contactPoint[i])
            for (int verg: graph.adjVerg[point])
            {
                ++pointTouchVerg[verg];
                if (pointTouchVerg[verg] == dfsInfo.contactPoint[i].size())
                {
                    ++curVergCnt;
                    curVerg = verg;
                }
            }
        //cout << i << ' ' << curVergCnt << '\n';
        if (curVergCnt == 0)
            return make_pair(-1, 0);
        else if (curVergCnt < minVergCnt)
        {
            minVergCnt = curVergCnt;
            minVergSeg = i;
            resVerg = curVerg;
        }
    }
    return make_pair(minVergSeg, resVerg);
}

bool getChainLine(Graph &graph, const int segNum, DfsInfo &dfsInfo, const int line);

bool getChainPoint(Graph &graph, const int segNum, DfsInfo &dfsInfo, const int point, bool isFirst = false)
{
    if (dfsInfo.used[point] == -1)
        return false;
    if (graph.takedPoint[point] && !isFirst)
    {
        dfsInfo.chain.push_back(point);
        return true;
    }
    dfsInfo.used[point] = -1;
    for (int to: graph.adjLine[point])
        if (getChainLine(graph, segNum, dfsInfo, to))
        {
            dfsInfo.chain.push_back(point);
            graph.takedPoint[point] = true;
            return true;
        }
    return false;
}

bool getChainLine(Graph &graph, const int segNum, DfsInfo &dfsInfo, const int line)
{
    if (dfsInfo.seg[line] != segNum)
        return false;
    if (getChainPoint(graph, segNum, dfsInfo, graph.lines[line].first) ||
        getChainPoint(graph, segNum, dfsInfo, graph.lines[line].second))
    {
        graph.takedLine[line] = true;
        return true;
    }
    return false;
}

void getNumbers(const Graph graph, const int verg, const int firstId,
                const int secondId, int &startPointId, int &finishPointId)
{
    for (int i = 0; i < graph.verges[verg].size(); ++i)
        if (graph.verges[verg][i] == graph.coord[firstId])
            startPointId = i;
        else if (graph.verges[verg][i] == graph.coord[secondId])
            finishPointId = i;
}

int mathMod(const int number, const int mod)
{
    return (number % mod + mod) % mod;
}

/**возращает внешнюю ломанную и индекс во внешней грани с которой она начинается*/
Polyline getExternalChain(const Polygon verg, const Polygon newVerg, int &startPointId)
{
    Polyline commonLine;
    set<Point> used;

    for (Point point: verg)
        used.insert(point);
    int i = newVerg.size() - 1;
    while (used.find(newVerg[i]) == used.end())
        --i;
    while (used.find(newVerg[i]) != used.end())
        i = (i + 1) % newVerg.size();
    startPointId = mathMod(i - 1, newVerg.size());
    commonLine.push_back(newVerg[startPointId]);
    while (used.find(newVerg[i]) == used.end())
    {
        commonLine.push_back(newVerg[i]);
        i = (i + 1) % newVerg.size();
    }
    commonLine.push_back(newVerg[i]);

    return commonLine;
}

Polyline getInternalChain(const PolygonPair split, const Point firstPoint)
{
    Polyline commonLine;
    set<Point> used;

    commonLine.push_back(split.secondPoly.back());
    for (int i = 0; split.secondPoly[i] != firstPoint; ++i)
        commonLine.push_back(split.secondPoly[i]);
    commonLine.push_back(firstPoint);

    return commonLine;
}

void setCoord(Graph &graph, Polyline &line, const vector<int> chain)
{
    if (line.size() < chain.size())
    {
        int diff = chain.size() - line.size();
        int cnt = (int)ceil((double)diff / (line.size() - 1));
        Polyline newLine;
        for (int i = 0; i + 1 < line.size(); ++i)
        {
            if (i * cnt >= diff)
                cnt = 0;
            Point v = (line[i + 1] - line[i]) / (cnt + 1);
            Point curPoint = line[i];
            for (int j = 0; j <= cnt; ++j)
            {
                newLine.push_back(curPoint);
                curPoint = curPoint + v;
            }
        }
        newLine.push_back(line.back());
        line = newLine;
    }
    for (int i = 1, e = chain.size() - 1; i < e; ++i)
        graph.coord[chain[i]] = line[i];
}

template <class T>
int deleteSubArr(vector<T> &arr, const int start, const int finish)
{
    if (start <= finish)
    {
        int d = finish - start + 1;
        for (int i = start, e = arr.size() - d; i < e; ++i)
            arr[i] = arr[i + d];
        arr.resize(arr.size() - d);
        return start;
    }
    else
    {
        arr.resize(start);
        return deleteSubArr(arr, 0, finish);
    }
}

template <class T>
void insertSubArr(vector<T> &arr, const vector<T> source, const int index)
{
    arr.resize(arr.size() + source.size());
    for (int i = arr.size() - 1; i >= index; --i)
        arr[i] = arr[i - source.size()];
    for (int i = 0; i < source.size(); ++i)
        arr[index + i] = source[i];
}

template <class T>
void replaceSubArr(vector<T> &arr, const vector<T> source, const int start, const int finish)
{
    insertSubArr(arr, source, deleteSubArr(arr, start, finish));
}

void addChain(const pair<int, int> minSeg, Graph &graph, DfsInfo &dfsInfo)
{
    getChainPoint(graph, minSeg.first + 1, dfsInfo, dfsInfo.contactPoint[minSeg.first][0], true);
    int startPointId = 0;
    int finishPointId = 0;
    getNumbers(graph, minSeg.second, dfsInfo.chain[0], dfsInfo.chain.back(), startPointId, finishPointId);
    Polyline chain;
    map<Point, int> pointId;
    for (int i = 0; i < graph.coord.size(); ++i)
        if (graph.takedPoint[i])
            pointId[graph.coord[i]] = i;

    if (minSeg.second == 0)
    {
        PolygonPair spawn = spawnPolygon(graph.verges[minSeg.second], startPointId, finishPointId);
        chain = getExternalChain(graph.verges[0], spawn.secondPoly, startPointId);
        if (chain[0] != graph.coord[dfsInfo.chain[0]])
            reverse(dfsInfo.chain.begin(), dfsInfo.chain.end());
        int prevSize = chain.size();
        setCoord(graph, chain, dfsInfo.chain);
        for (int i = mathMod(startPointId - 1, spawn.secondPoly.size()); spawn.secondPoly[i] != chain.back();
            i = mathMod(i - 1, spawn.secondPoly.size()))
        {
            auto it = pointId.find(spawn.secondPoly[i]);
            if (it != pointId.end())
            {
                graph.adjVerg[it->second][find(graph.adjVerg[it->second].begin(), graph.adjVerg[it->second].end(), 0) -
                    graph.adjVerg[it->second].begin()] = graph.verges.size();
            }
        }
        replaceSubArr(spawn.secondPoly, chain, startPointId, mathMod(startPointId + prevSize - 1, spawn.secondPoly.size()));
        startPointId = find(spawn.firstPoly.begin(), spawn.firstPoly.end(), chain[0]) - spawn.firstPoly.begin();
        replaceSubArr(spawn.firstPoly, chain, startPointId, (startPointId + prevSize - 1) % spawn.firstPoly.size());
        graph.verges[0] = spawn.firstPoly;
        graph.adjVerg[dfsInfo.chain[0]].push_back(graph.verges.size());
        graph.adjVerg[dfsInfo.chain.back()].push_back(graph.verges.size());
        for (int i = 1, e = dfsInfo.chain.size() - 1; i < e; ++i)
        {
            graph.adjVerg[dfsInfo.chain[i]].push_back(0);
            graph.adjVerg[dfsInfo.chain[i]].push_back(graph.verges.size());
        }
        graph.verges.push_back(spawn.secondPoly);
    }
    else
    {
        PolygonPair split = splitPolygon(graph.verges[minSeg.second], startPointId, finishPointId);
        chain = getInternalChain(split, graph.coord[dfsInfo.chain[0]]);
        reverse(dfsInfo.chain.begin(), dfsInfo.chain.end());
        int prevSize = chain.size();
        setCoord(graph, chain, dfsInfo.chain);
        for (int i = split.secondPoly.size() - 2; split.secondPoly[i] != chain.back();
            i = mathMod(i - 1, split.secondPoly.size()))
        {
            auto it = pointId.find(split.secondPoly[i]);
            if (it != pointId.end())
            {
                graph.adjVerg[it->second][find(graph.adjVerg[it->second].begin(), graph.adjVerg[it->second].end(), minSeg.second) -
                    graph.adjVerg[it->second].begin()] = graph.verges.size();
            }
        }
        replaceSubArr(split.secondPoly, chain, split.secondPoly.size() - 1, prevSize - 2);
        reverse(chain.begin(), chain.end());
        replaceSubArr(split.firstPoly, chain, split.firstPoly.size() - prevSize + 1, 0);
        graph.verges[minSeg.second] = split.firstPoly;
        graph.adjVerg[dfsInfo.chain[0]].push_back(graph.verges.size());
        graph.adjVerg[dfsInfo.chain.back()].push_back(graph.verges.size());
        for (int i = 1, e = dfsInfo.chain.size() - 1; i < e; ++i)
        {
            graph.adjVerg[dfsInfo.chain[i]].push_back(minSeg.second);
            graph.adjVerg[dfsInfo.chain[i]].push_back(graph.verges.size());
        }
        graph.verges.push_back(split.secondPoly);
    }
    //--------------------------------
    cout << "Chain:\n";
    for (int point: dfsInfo.chain)
        cout << point << ' ';
    cout << '\n';
    cout << "AdjVerg:\n";
    for (int i = 0; i < graph.adjVerg.size(); ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < graph.adjVerg[i].size(); ++j)
            cout << graph.adjVerg[i][j] << ' ';
        cout << '\n';
    }
    //--------------------------------
}

int gammaStep(Graph &graph)
{
    DfsInfo dfsInfo(graph.adjLine.size(), graph.lines.size());
    int result = 0;
    for (int i = 0; i < graph.lines.size(); ++i)
        if (!graph.takedLine[i] && dfsInfo.seg[i] == 0)
        {
            dfsInfo.contactPoint.push_back(vector<int>());
            result = 1;
            dfsLine(graph, i, dfsInfo);
        }
    if (!result)
        return result;
    pair<int, int> minSeg = getMinSeg(graph, dfsInfo);
    //---------------------
    cout << "Segments:\n";
    for (auto contacts: dfsInfo.contactPoint)
    {
        for (int v: contacts)
            cout << v << ' ';
        cout << '\n';
    }
    //---------------------
    if (minSeg.first == -1)
        return -1;
    //--------------------
    cout << "verge: " << minSeg.second << '\n';
    //minSeg.second = 0;
    //--------------------
    addChain(minSeg, graph, dfsInfo);
    return result;
}

bool gammaInit(Graph &graph)
{
    vector<int> cycle;
    vector<int> used(graph.adjLine.size(), 0);
    if (!getCycle(graph, cycle, used))
        return false;
    else
    {
        const int TESTCOUNT = 128;
        for (int i = 0; i < TESTCOUNT; ++i)
        {
            vector<int> curCycle;
            fill(used.begin(), used.end(), 0);
            getCycle(graph, curCycle, used);
            if (curCycle.size() > cycle.size())
            {
                cycle.resize(curCycle.size());
                copy(curCycle.begin(), curCycle.end(), cycle.begin());
            }
            curCycle.clear();
        }
    }
    layCycle(graph, cycle);
    //------------------------
    cout << "Cycle:\n";
    for (int v: cycle)
        cout << v << ' ';
    cout << '\n';
    //------------------------
    return true;
}

int main()
{
    cout << "seed: " << seed << '\n';
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph.lines.push_back(make_pair(a, b));
        graph.adjLine[a].push_back(i);
        graph.adjLine[b].push_back(i);
    }
    if (!gammaInit(graph))
    {
        cout << "Cycle not found\n";
        return 0;
    }
    int gd = DETECT;
    int gm = 0;
    initgraph(&gd, &gm, "");

    cout << graph.verges[0].size() << '\n';

    int lastIterationResult = gammaStep(graph);
    while (lastIterationResult == 1)
        lastIterationResult = gammaStep(graph);
    if (lastIterationResult == -1)
    {
        cout << "Graph is not be drown\n";
        closegraph();
        return 0;
    }
    drawGraph(graph, 325, 225, 35);

    char c = '\0';
    cin >> c;
    closegraph();

    return 0;
}
