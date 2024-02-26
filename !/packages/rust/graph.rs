pub struct Graph {
    adj: Vec<Vec<i32>>,
    n: usize,
    visited: Vec<bool>,
    roots: Vec<i32>,
}

impl Graph {
    pub fn new(no_of_nodes: usize, fill: bool) -> Self {
        let mut graph = Graph {
            adj: vec![vec![]; no_of_nodes],
            n: no_of_nodes,
            visited: vec![false; no_of_nodes],
            roots: vec![],
        };

        if fill {
            graph.dfs();
        }

        graph
    }

    pub fn clear(&mut self) {
        self.visited.clear();
    }

    pub fn dfs(&mut self) {
        self.visited = vec![false; self.n];

        if self.roots.is_empty() {
            self.roots.push(0);
        }

        let roots = self.roots.clone();
        for &root in &roots {
            self.dfs_helper(root, 0, -1, root, true);
        }
    }

    fn dfs_helper(&mut self, node: i32, level: i32, parent: i32, root: i32, modify: bool) {
        self.visited[node as usize] = true;

        let adj_node = self.adj[node as usize].clone();
        for &to in &adj_node {
            if !self.visited[to as usize] {
                self.dfs_helper(to, level + 1, node, root, modify);
            }
        }
    }

    pub fn bfs(&mut self, root: i32) {
        let mut q = VecDeque::new();
        q.push_back(root);
        self.visited[root as usize] = true;

        while let Some(vertex) = q.pop_front() {
            for &u in &self.adj[vertex as usize] {
                if !self.visited[u as usize] {
                    self.visited[u as usize] = true;
                    q.push_back(u);
                }
            }
        }
    }
}
