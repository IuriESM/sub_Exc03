//#define EIGENLIB			// uncomment to use Eigen linear algebra library

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, ONLY between the MODELBEGIN and MODELEND words



// ================================================================
// ----------------------------------------------------------------
// ================================================================
// EXERC�CIO 03 -|-|-|-|

EQUATION("Ms")
/*
msi,t - � a participa��o de mercado da empresa i no per�odo t; 

Ms = Ms_t-1 (1+u_j ((co/co_med) - 1))

Participa��o de Mercado = Participa��o de Mercado no Per�odo T-1 * (1 + par�metro de ajuste da participa��o de mercado do setor * ((competitividade da empresa i no per�odo t / competitividade m�dia do setor j no per�odo t))

*/

v[0] = VL("Ms", 1);
v[1] = V("adjs_ms");
v[2] = V("Comp");
v[3] = V("Comp_Ave");

v[4] = v[0]*(1+v[1]*(v[2]/v[3]-1));

RESULT(v[4])

EQUATION("Comp")
/*
Comp = (q^(e^q))/ p^(e^p)

Competitividade da empresa i no per�odo t = qualidade da empresa i no per�odo t^(elasticidade da qualidade) / pre�o da empresa i no per�odo t^(elasticidade do pre�o)

pow( a, b ): the power b of a
*/
v[5] = V("Quali");
v[6] = V("Price");
v[7] = V("elas_q");
v[8] = V("elas_p");

v[9] = (pow(v[5],v[7]))/(pow(v[6],v[8]));
RESULT(v[9])


EQUATION("Quali")
/*
Quali = q_t-1 + c_t 

c_t = U(q^min, q^max)

qualidade da empresa i no per�odo t = qualidade da empresa i no per�odo t-1 + componente aleat�rio seguindo uma distribui��o uniforme (qmin = 0 e qmax = 1)
*/

v[9] = VL("Quali", 1);
v[10] = V("c_aleator");

v[11] = v[9] + v[10];

RESULT(v[11])


EQUATION("c_aleator")
/*
componente aleat�rio seguindo uma distribui��o uniforme (qmin = 0 e qmax = 1)
*/

v[12] = V("q_min");
v[13] = V("q_max");
v[16] = uniform(v[14], v[15]);

RESULT(v[16])









// ================================================================
// ----------------------------------------------------------------
// ================================================================

// ================================================================
// ----------------------------------------------------------------
// ================================================================

// ================================================================
// ----------------------------------------------------------------
// ================================================================

EQUATION("Avg_Price")

/*
Mostra o que a Macro AVE faz

*/

v[0]=0; // iniciando o v[0]; pode ocorrer de n�o ser zero
v[2]=0;
CYCLE(cur, "FIRM")
{
	v[1] = VS(cur, "Price"); // VS= "S" � Especifico 
	v[0] = v[0] + v[1]; // sum of prices
	v[2] = v[2] + 1;  // count firms 
}
v[3] = v[0]/v[2];

RESULT(v[3])



//RESULT(AVE("Price"))



EQUATION("Price")
/*
Pre�o = Grau de Monop�lio*Pre�o desejado + (1 - Grau de Monop�lio)*Pre�o m�dio no T-1

p_t = theta*pd + (1 - theta)*p_t-1

*/

v[0] = V("theta");
v[1] = V("Desired_Price");
v[2] = AVEL("Price", 1); 
// v[2] = VL(Avg_Price, 1)
v[3] = v[0]*v[1]+(1-v[0])*v[2]; 
RESULT(v[3])


EQUATION("Desired_Price")

/*
Pre�o Desejado = (1 + Markup da firma)*Custo da firma

pd = (1 + u)*c
*/

v[0] = V("markup");
v[1] = V("Cost");
v[2] = (1+v[0])*v[1];

RESULT(v[2])



EQUATION("Cost")

/*
Pre�o Desejado = (1 + Markup da firma)*Custo da firma

pd = (1 + u)*c
*/

v[0] = V("avg");
v[1] = V("sd");
v[2] = norm(v[0], v[1]);

RESULT(v[2])











MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}

