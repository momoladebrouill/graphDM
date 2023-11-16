type uf =  {
    parent : int array;
    rank : int array;
    nelements : int;
}

let makesets n =
  {
    parent = Array.init n  Fun.id;
    rank = Array.make n 0;
    nelements = n
}

let rec find uf i =
  let p = uf.parent.(i) in
  if p = i then i
  else begin
    let r = find uf p in
    uf.parent.(i) <- r; r 
  end

let union uf x y =
  let rootx = find uf x in
  let rooty = find uf y in
  if rootx <> rooty then
    let ri,rj = uf.rank.(rootx),uf.rank.(rooty) in
    (
      if ri < rj then uf.parent.(rootx) <- rooty
      else if ri > rj then uf.parent.(rooty) <- rootx
      else uf.parent.(rootx) <- rooty; uf.rank.(rooty) <- rj + 1
    )

type graph = 
  {
    (*src, poids , dest*)
    mutable tas :(int*int*int)  list;
    nsommets : int;
  }

let min_poids (_,p,_) (_,p',_) = 
  Stdlib.compare p' p

let get f = 
  f := List.sort min_poids !f;
  let t::q = !f in
  f := q;
  t
let add f x =
  f:= x::!f

let makegraph n = 
  { 
    tas = [];
    nsommets = n 
   }

let add_arrete g x poids y =
  if List.exists (fun (x',p,y') -> (x = x' && y = y') || (x' = y && y' = x)) g.tas || x = y then () 
  else g.tas <- (x,poids,y)::g.tas

let fillgraph g n =
  for i = 0 to n do 
    add_arrete g (Random.int g.nsommets) (Random.int 50) (Random.int g.nsommets)
  done


let kruskal g =
  let s = makesets g.nsommets in
  let f = ref [] in
  List.iter (add f) g.tas;
  let t = ref [] in
  while List.length !t < g.nsommets - 1 do
    let (x,p,y) = get f in
    if find s x <> find s y then
      (t := (x,y)::!t;
      union s x y)
  done;
  !t

