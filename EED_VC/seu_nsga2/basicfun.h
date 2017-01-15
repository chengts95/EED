#ifndef BASICFUNH
#define BASICFUNH

#include "typedef.h"
#include <fstream>

  // allocate.cpp
  void allocate_ind(int nreal,int nbin,int *nbits,int nobj,int ncon,
                             individual *ind);
  void allocate_pop(int nreal,int nbin,int *nbits,int nobj,int ncon,
                             population *pop, int size);

  void deallocate_ind(int nreal,int nbin,int ncon,individual *ind);
  void deallocate_pop(int nreal,int nbin,int ncon,population *pop, int size);

  // rand.cpp
  void advance_random();
  void warmup_random(double seed);

  void deb_randomize();
  double randomperc();
  int rnd(int low, int high);
  double rndreal(double low, double high);

  // initialize.cpp
  void initialize_ind (int nreal,
                     double *min_realvar,double *max_realvar,
                     int nbin,int *nbits,
                     individual *ind);
  void initialize_pop (int popsize,
                     int nreal,
                     double *min_realvar,double *max_realvar,
                     int nbin,int *nbits,
                     population *pop);
  // decode.cpp
  void decode_ind (int nbin,int *nbits,
                   double *min_binvar, double *max_binvar,individual *ind);
  void decode_pop (int popsize,int nbin,int *nbits,
                   double *min_binvar, double *max_binvar,population *pop);

  // eval.cpp
  void evaluate_ind(int ncon,individual *ind,
                    void (*funrb)(double*, double*, int**, double*, double*));
  void evaluate_pop (int popsize,int ncon,population *pop,
                    void (*funrb)(double*, double*, int**, double*, double*));

  //crossover.cpp
  void realcross (int nreal,
                double pcross_real,double eta_c,
                double *min_realvar,double *max_realvar,
                int &nrealcross,
                individual *parent1, individual *parent2,
                individual *child1, individual *child2);
  void bincross (int nbin,
               double pcross_bin,int *nbits,
               int &nbincross,
               individual *parent1, individual *parent2,
               individual *child1, individual *child2);
  void crossover (int nreal,
                double pcross_real,double eta_c,
                double *min_realvar,double *max_realvar,
                int &nrealcross,
                int nbin,
                double pcross_bin,int *nbits,
                int &nbincross,
                individual *parent1, individual *parent2,
                individual *child1, individual *child2);

  //mutation
  void bin_mutate_ind (int nbin,int *nbits,double pmut_bin,
                     int &nbinmut,
                     individual *ind);
  void real_mutate_ind (int nreal,double pmut_real, double eta_m,
                      double *min_realvar,double *max_realvar,
                      int &nrealmut,
                      individual *ind);
   void mutation_ind(int nreal,double pmut_real, double eta_m,
                   double *min_realvar,double *max_realvar,
                   int &nrealmut,
                   int nbin,int *nbits,double pmut_bin,
                   int &nbinmut,
                   individual *ind);
   void mutation_pop(int popsize,
                     int nreal,double pmut_real, double eta_m,
                     double *min_realvar,double *max_realvar,int &nrealmut,
                     int nbin,int *nbits,double pmut_bin,int &nbinmut,
                     population *pop);
  //list.cpp
  void insert(list *node, int x);
  list* del(list *node);

   //sort.cpp
   void quicksort_front_obj(population *pop, int objcount, int obj_array[], int obj_array_size);
   void q_sort_front_obj(population *pop, int objcount, int obj_array[], int left, int right);
   void quicksort_dist(population *pop, int *dist, int front_size);
   void q_sort_dist(population *pop, int *dist, int left, int right);

  // crowddist.cpp
   void assign_crowding_distance_list(int nobj,population *pop,
                                      list *lst, int front_size);
   void assign_crowding_distance_indices(int nobj,population *pop,
                                        int c1, int c2);
   void assign_crowding_distance(int nobj,population *pop,
                            int *dist, int **obj_array, int front_size);

  // dominance.cpp
  int check_dominance(int nobj,individual *a, individual *b);

  // rank.cpp

  void assign_rank_and_crowding_distance(int popsize,int nobj,
                                         population *new_pop);

  // tourselect.cpp
  void selection (int popsize,int nobj,
                int nreal,
                double pcross_real,double eta_c,
                double *min_realvar,double *max_realvar,
                int &nrealcross,
                int nbin,
                double pcross_bin,int *nbits,
                int &nbincross,
                population *old_pop, population *new_pop);

 // merge.cpp
 void copy_ind(int nobj,int ncon,
              int nreal,int nbin,int *nbits,
              individual *ind1, individual *ind2);
 void merge(int popsize,
           int nobj,int ncon,
           int nreal,int nbin,int *nbits,
           population *pop1, population *pop2, population *pop3);

 //fillnds.cpp
 void crowding_fill(int popsize,int nobj,
                   int ncon,
                   int nreal,int nbin,int *nbits,
                   population *mixed_pop, population *new_pop,
                   int count, int front_size, list *elite);
 void fill_nondominated_sort(int popsize,int nobj,int ncon,
                       int nreal,int nbin,int *nbits,
                       population *mixed_pop, population *new_pop);

#endif
