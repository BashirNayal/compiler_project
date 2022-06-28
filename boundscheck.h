#define plus_infinity INT_MAX
#define min_infinity INT_MIN


bool do_bounds_check(llvm::Module &M);
bool do_bounds_check_elim(llvm::Module &M);



typedef struct var_range_s {
    int lower_bound;
    int upper_bound;
    struct {
        bool goes_up;
        bool goes_down;
        bool constant;
        bool cyclic_def;
        llvm::Value *conditinoals[512];
        int split_at[512];
    } meta_data;

} var_range_st;
