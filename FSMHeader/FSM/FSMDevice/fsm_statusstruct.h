#ifndef FSM_STATUSSTRUCT
#define FSM_STATUSSTRUCT
#define srow_cnt 8
#define scolumn_cnt 12
#define status_cnt srow_cnt*scolumn_cnt
struct fsm_status_element
{
char state[32];
char fsmdevcode[32];
char comment[128];
char fullstate[128];
short devid;
};
struct fsm_statusstruct
{
struct fsm_status_element statel[srow_cnt][scolumn_cnt];
};


#endif // FSM_STATUSSTRUCT

