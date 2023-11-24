

struct Edge {
    pub src: i64,
    pub dst: i64,
}

struct Graph {
    pub edges: Vec<Edge>,
}

fn main() {
    let graph = Graph { edges: Vec::new() };
    println!("Hello, world {}!", graph.edges.len());
}
