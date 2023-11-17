type arrete = 
  { 
    poids : int;
    src : int;
    dst : int;
}

type graph = 
  {
   ladj : arrete list array;
   distance : int array;
   n : int;
  }


let maketasmin g =
  ref (List.map snd (List.sort Stdlib.compare (List.init g.n (fun i->g.distance.(i),i))))

let compare g a b =
  Stdlib.compare g.distance.(a) g.distance.(b)

let nonvide tas =
  !tas <> []

let insere g tas elem =
  tas := List.sort (compare g) (elem::!tas)

let retire g tas =
  let hd = List.hd !tas in
  tas := List.tl !tas;
  hd

let djikstra g src =
  List.iter (fun i-> g.distance.(i) <- max_int) (List.init g.n Fun.id);
  g.distance.(src) <- 0;
  let a_traiter = ref [src] in 
  while nonvide a_traiter do 
    let x = retire g a_traiter in
    let ppi = g.distance.(x) in (*poids pour ici*)
    List.iter (fun arete -> if g.distance.(arete.dst) > ppi + arete.poids 
      then g.distance.(arete.dst) <- ppi + arete.poids; insere g a_traiter arete.dst) g.ladj.(x)
  done

let makegraph () =
  let n = 4 in
  let ladj = Array.make n [] in
  List.iter (fun (src,poids,dst)-> ladj.(src)<-{src = src; poids = poids; dst = dst} :: ladj.(src))
  [(0,5,2);(0,2,1);(0,18,3);(1,3,2);(1,15,3);(2,4,3)];
  { ladj = ladj; n = n; distance = Array.make n 0}
  
      
