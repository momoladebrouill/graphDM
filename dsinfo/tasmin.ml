type tasmin = 
  {
    tas : int array;
    mutable size : int;
}

let inittasmin _N = 
  {
    tas = Array.make _N 0;
    size = 0;
}

let compare = (<)

let parent i =
  (i-1) / 2

let filsGauche i =
  2 * i + 1

let filsDroite i =
  2 * i + 2

let swap a i j =
  let a = a.tas in
  let temp = a.(i) in
  a.(i) <- a.(j);
  a.(j) <- temp

let rec fixins i t  = 
  if i > 0 && (compare t.tas.(parent i) t.tas.(i)) then (
    swap t (parent i) i;
    fixins (parent i) t
  )

let insere t x =
  t.tas.(t.size) <- x;
  t.size <- t.size + 1;
  fixins t.size t

let indiceminfils i t = 
  (if compare t.tas.(filsGauche i)  t.tas.(filsDroite i) then filsGauche  else filsDroite) i

let rec fixret i t =
  if filsDroite i < t.size && compare t.tas.(indiceminfils i t) t.tas.(i) then
    let j = indiceminfils i t in
    swap t j i;
    fixret j t

let retire t =
  swap t 0 (t.size - 1);
  fixret 0 t;
  t.size <- t.size - 1;
  t.tas.(t.size)

let print_tas t =
  Array.iter (Printf.printf "%d ") t.tas;
  print_newline ()

let dot () =
  let t = inittasmin 10 in
  for i = 0 to 8 do
    let d = Random.int 50 in
    Printf.printf "Insertion de %d : " d;
    insere t d;
    print_tas t
 done;
 t
