type graph = 
  {
    qqty : int;
    ladj : int list array
   }
 
let rec dfs g parcouru action i  =
  parcouru.(i) <- true;
  List.iter (dfs g parcouru action) (List.filter (fun i-> not parcouru.(i)) g.ladj.(i));
  action i

let init_graph qqty = 
  {
    qqty = qqty;
    ladj = Array.make qqty []
}

let ajout_arrete g x y =
  if not (List.mem y g.ladj.(x)) then
  g.ladj.(x) <- y::g.ladj.(x)

let reverse_graph g =
  let rg = init_graph g.qqty in
  Array.iteri (fun x l ->
    List.iter (fun y ->
      ajout_arrete rg y x
    ) l
  ) g.ladj;
  rg

let kosaraju g =
  let parcouru = Array.make g.qqty false in (*initialise DFS pour G*)
  let temps_sortie = Array.make g.qqty 0 in (*temps de sortie du DFS*)
  let temps = ref 0 in 
  
  let action i =
    temps_sortie.(i) <- !temps;
    incr temps
  in
  let rec loop () =
    match Array.find_index (not) parcouru with
    None -> ()
    | Some i -> dfs g parcouru action i; loop ()
  in loop (); (* tant qu'il y a un sommet inconnu, on lance un dfs depuis ce sommmet*)
  
  let s = Array.init g.qqty (fun i-> (temps_sortie.(i),i)) in
  Array.sort (fun a b -> Stdlib.compare b a) s;(* on trie les sommets dans l'ordre décroissant du temps de sortie*)
  let parcouruR = Array.make g.qqty false in (*initialise DFS pour rG*)
  let rg = reverse_graph g in
  let comp = Array.make g.qqty (-1) in (*numéro de la CFC pour chaque sommet*)
  
  let action parcu i =
    comp.(i)<-parcu 
  in

  let rec loop n =
    match Array.find_index (fun (_,i) -> not parcouruR.(i)) s with
    None -> ()
    | Some x -> dfs rg parcouruR (action n) x; loop (n+1)
  in aux 0;

  comp


let g = init_graph 6
let init () =
  List.iter (fun (x,y) -> ajout_arrete g (x-1) (y-1)) 
    [(1,2);(2,3);(3,1);(3,4);(4,5);(5,6);(6,4)]

