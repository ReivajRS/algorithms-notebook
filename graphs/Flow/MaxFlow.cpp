// Time complexity O(V^2 * E)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, ll, ll> edge;

const ll INF = 1e18;        // Suficientemente grande

class max_flow {
 private:
    int V;              // Numero de vertices
    vector<edge> EL;    // Lista de aristas
    vector<vi> AL;      // Lista de adyacencia con los indices de las aristas
    vi d, last;         // Vector de distancias y ultimas aristas
    vector<ii> p;       // Vector para el camino. first = id del nodo, second = indice en la lista de aristas

    bool BFS(int s, int t) {                                // Encontrar un augmenting path
        d.assign(V, -1); d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});                              // Guardar el sp tree del BFS
		while (!q.empty()) {
        int u = q.front(); q.pop();
            if (u == t) break;                              // Parar si se llega al sink t
            for (auto &idx : AL[u]) {                       // Explora los vecinos de u
                auto &[v, cap, flow] = EL[idx];             // Arista guardada en EL[idx]
                if ((cap-flow > 0) && (d[v] == -1))         // Arista residual positiva
                d[v] = d[u]+1, q.push(v), p[v] = {u, idx};  // 3 lineas en una B)
            }
        }
        return d[t] != -1;                                  // Tiene un augmenting path
    }

    ll DFS(int u, int t, ll f = INF) {                      // Ir de s->t
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i){ // Desde la ultima arista
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u]+1) continue;                   // No es parte del grafo de niveles
            if (ll pushed = DFS(v, t, min(f, cap-flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i]^1]);       // Arista de regreso
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

 public:
    max_flow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    // Si se agrega una arista bidireccional u<->v con peso w en el grafo de flujo,
    // asigna directed = false. El valor por defecto es true (Arista dirigida)
    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return;                          // Por seguridad: Evita ciclos en el mismo nodo
        EL.emplace_back(v, w, 0);                    // u->v, cap w, flow 0
        AL[u].push_back(EL.size()-1);                // Para recordar el indice
        EL.emplace_back(u, directed ? 0 : w, 0);     // Arista de regreso
        AL[v].push_back(EL.size()-1);                // Para recordar el indice
    }

    ll dinic(int s, int t) {
        ll mf = 0;                      // mf = Max flow
        while (BFS(s, t)) {             // Time complexity O(V^2*E)
            last.assign(V, 0);          // Aceleracion importante
            while (ll f = DFS(s, t))    // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int main() {
    // Leer numero de nodos(V), source(s), sink(t)
    // De preferencia asignar s = 0, t = V-1
    // max_flow mf(V);
    // Crear aristas usando el metodo add_edge(u, v, w);

  return 0;
}