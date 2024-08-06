% AXIOMS

fof(perp_sym,axiom, ! [L1,L2] : (perp(L1,L2) => perp(L2,L1))).
fof(midpoint_unique,axiom, ! [M1,M2,P1,P2] : ((midpoint(M1,P1,P2) & midpoint(M2,P1,P2)) => (M1=M2) )).
fof(center_unique,axiom, ! [C,C1,C2] : ((center(C1,C) & center(C2,C)) => (C1=C2) )).

fof(inc_A_C_ac,axiom, (inc(pA,ac) & inc(pC,ac) ) ).
fof(inc_B_C_bc,axiom, (inc(pB,bc) & inc(pC,bc) ) ).
fof(inc_A_B_ab,axiom, (inc(pA,ab) & inc(pB,ab) ) ).
fof(perp_ha_BC,axiom, (perp(ha,bc) & inc(pA,ha) ) ).
fof(perp_hb_AC,axiom, (perp(hb,ac) & inc(pB,hb) ) ).
fof(perp_hc_AB,axiom, (perp(hc,ab) & inc(pC,hc) ) ).
fof(inc_Ha_ha,axiom, (inc(pHa,ha) & inc(pHa,bc) ) ).
fof(inc_Hb_hb,axiom, (inc(pHb,hb) & inc(pHb,ac) ) ).
fof(inc_Hc_hc,axiom, (inc(pHc,hc) & inc(pHc,ab) ) ).
fof(pMa_def,axiom,(midpoint(pMa,pB,pC) ) ).
fof(pMb_def,axiom,(midpoint(pMb,pA,pC) ) ).
fof(pMc_def,axiom,(midpoint(pMc,pA,pB) ) ).
fof(inc_cc,axiom,(inc_c(pA,cc) & inc_c(pB,cc) & inc_c(pC,cc) ) ).
fof(pOc_def,axiom,(center(pOc,cc) ) ).

fof(ratio23_AGAMa,axiom,(ratio23(pA,pG,pA,pMa) ) ).
fof(ratio23_BGBMb,axiom,(ratio23(pB,pG,pB,pMb) ) ).
fof(ratio23_CGCMc,axiom,(ratio23(pC,pG,pC,pMc) ) ).
fof(ratio13_OGOH,axiom,(ratio13(pOc,pG,pOc,pH) ) ).

fof(unique_ratio23_1,axiom,! [A,B,X,Y]: (ratio23(A,X,A,B) & ratio23(A,Y,A,B) => X=Y) ).
fof(unique_ratio23_2,axiom,! [A,B,X,Y]: (ratio23(A,B,A,X) & ratio23(A,B,A,Y) => X=Y) ).

fof(ab_unique,axiom, ! [L] : ( inc(pA,L) & inc(pB,L) => L=ab )).
fof(ac_unique,axiom, ! [L] : ( inc(pA,L) & inc(pC,L) => L=ac )).
fof(bc_unique,axiom, ! [L] : ( inc(pB,L) & inc(pC,L) => L=bc )).
fof(sides_distinct,axiom, ( ab!=ac & ab!=bc & ac!=bc )).

fof(haA,axiom, ! [H] : ((perp(H,bc) & inc(pA,H)) => ha = H ) ).
fof(hbB,axiom, ! [H] : ((perp(H,ac) & inc(pB,H)) => hb = H ) ).
fof(hcC,axiom, ! [H] : ((perp(H,ab) & inc(pC,H)) => hc = H ) ).

fof(pHa_def,axiom, ! [H1] : ((inc(H1,ha) & inc(H1,bc)) => H1 = pHa ) ).
fof(pHb_def,axiom, ! [H1] : ((inc(H1,hb) & inc(H1,ac)) => H1 = pHb ) ).
fof(pHc_def,axiom, ! [H1] : ((inc(H1,hc) & inc(H1,ab)) => H1 = pHc ) ).
fof(cc_unique,axiom, ! [C] : ( (inc_c(pA,C) & inc_c(pB,C) & inc_c(pC,C) ) =>  (C=cc) ) ).

fof(inc_Ma_bc,axiom,(inc(pMa,bc)) ).
fof(inc_Mb_ac,axiom,(inc(pMb,ac)) ).
fof(inc_Mc_ab,axiom,(inc(pMc,ab)) ).

fof(pH_def,axiom,(inc(pH,ha) & inc(pH,hb) & inc(pH,hc) ) ).
fof(pH_unique1,axiom, ! [H1] : (inc(H1,ha) & (inc(H1,hb)) => H1 = pH ) ).
fof(pH_unique2,axiom, ! [H1] : (inc(H1,ha) & (inc(H1,hc)) => H1 = pH ) ).
fof(pH_unique3,axiom, ! [H1] : (inc(H1,hb) & (inc(H1,hc)) => H1 = pH ) ).

% CONJECTURES

%-----------------------
% lemma 3: A_B_Ma:
%-----------------------
%fof(th_A_B_Ma,conjecture, ( ( midpoint(pMa1,pB,pC) ) => ( pMa=pMa1 ) ) ).


%-----------------------
%lemma 6: A_B_G:
%-----------------------
%fof(th_A_B_G,conjecture, (ratio23(pB,pG1,pB,pMb1) & midpoint(pMb1,pA,pC) => ( pG=pG1 ) ) ).


%-----------------------
%lemma 10: A_B_H:
%-----------------------
%fof(th_A_B_H,conjecture, ( ( inc(pA,ha1) & inc(pH1,ha1) & inc(pB,hb1) & inc(pH1,hb1) & inc(pB,a1) & perp(a1,ha1) & inc(pA,b1) & perp(b1,hb1) & inc(pC,a1) & inc(pC,b1) ) => ( pH1=pH ) ) ).


%-----------------------
%lemma 32: A_Ha_O:
%-----------------------
%fof(th_A_Ha_O,conjecture, ( ( inc(pA,ha1) & inc(pHa1,ha1) & perp(ha1,a1) & inc(pHa1,a1) & inc_c(pA,k) & center(pO1,k) & inc_c(pB,k) & inc(pB,a1) & inc_c(pC,k) & inc(pC,a1) ) => ( pHa=pHa1 &  pOc=pO1 ) ) ).


%-----------------------
%lemma 342: Ma_Mb_G:
%-----------------------
fof(th_Ma_Mb_G,conjecture, (midpoint(pMa1,pB,pC) & ratio23(pA,pG1,pA,pMa1) & ratio23(pB,pG1,pB,pMb1) => ( pMa=pMa1 & pMb=pMb1 & pG=pG1 ) ) ).
