% AXIOMS

fof(line_unique, axiom, ![P1, P2, L1, L2] : (line(P1, P2, L1) & line(P1, P2, L2) & (P1 != P2) => (L1 = L2))).
fof(line_inc, axiom, ![P1, P2, L] : (line(P1, P2, L) => (inc(P1, L) & inc(P2, L)))).
fof(inc_line, axiom, ![P1, P2, L] : (inc(P1, L) & inc(P2, L) & (P1 != P2) => line(P1, P2, L))).
%fof(ex_line, axiom, ![P1, P2] : (? [L] : line(P1, P2, L))).
fof(intersect_unique, axiom, ![P1, P2, L1, L2] : ((L1 != L2) & inc(P1, L1) & inc(P1, L2) & inc(P2, L1) & inc(P2, L2) => (P1 = P2))).
fof(intersect_unique2, axiom, ![P1, P2, P3, L1, C1] : (inc(P1, L1) & inc_c(P1, C1) & inc(P2, L1) & inc_c(P2, C1) & inc_c(P3, C1) & inc(P3, L1) & (P1 != P2) & (P1 != P3) => (P2 = P3))).
fof(intersect_unique3, axiom, ![P1, P2, P3, C1, C2] : ((C1 != C2) & inc_c(P1, C1) & inc_c(P2, C1) & inc_c(P3, C1) & inc_c(P1, C2) & inc_c(P2, C2) & inc_c(P3, C2) & (P1 != P2) & (P1 != P3) => (P2 = P3))).
fof(perp_sym, axiom, ![L1, L2] : (perp(L1, L2) => perp(L2, L1))).
fof(perp_unique, axiom, ![P, L, L1, L2] : (perp(L1, L) & inc(P, L1) & perp(L2, L) & inc(P, L2) => (L1 = L2))).
fof(midpoint_sym, axiom, ![P1, P2, M] : (midpoint(M, P1, P2) => midpoint(M, P2, P1))).
fof(distinct_midpoint1, axiom, ![P1, P2, M] : (P1 != P2 & midpoint(M, P1, P2) => M != P1)).
fof(distinct_midpoint2, axiom, ![P1, P2, M] : (P1 != P2 & midpoint(M, P1, P2) => M != P2)).
fof(midpoint_unique, axiom, ![M1, M2, P1, P2] : (midpoint(M1, P1, P2) & midpoint(M2, P1, P2) => M1 = M2)).
%fof(ex_midpoint, axiom, ![P1, P2] : (?[M] : midpoint(M, P1, P2))).
fof(midpoint_degenerate, axiom, ![P] : midpoint(P, P, P)).
fof(circle_center, axiom, ![K, Pc, Px] : (circle(K, Pc, Px) => center(Pc, K))).
fof(circle_point, axiom, ![K, Pc, Px] : (circle(K, Pc, Px) => inc_c(Px, K))).
fof(circle_def, axiom, ![K, Pc, Px] : (Pc != Px & center(Pc, K) & inc_c(Px, K) => circle(K, Pc, Px))).
fof(center_unique, axiom, ![C, C1, C2] : (center(C1, C) & center(C2, C) => C1 = C2)).
fof(circle_unique, axiom, ![O, P, C1, C2] : (center(O, C1) & center(O, C2) & inc_c(P, C1) & inc_c(P, C2) => C1 = C2)).
fof(circle3, axiom, ![P1, P2, P3, C1, C2] : (P1 != P2 & P1 != P3 & P2 != P3 & inc_c(P1, C1) & inc_c(P2, C1) & inc_c(P3, C1) & inc_c(P1, C2) & inc_c(P2, C2) & inc_c(P3, C2) => C1 = C2)).
fof(circle_over_1, axiom, ![P1, P2, K, M] : (circle_over(K, P1, P2) & midpoint(M, P1, P2) => center(M, K) & inc_c(P1, K) & inc_c(P2, K))).
fof(circle_over_2, axiom, ![P1, P2, K, M] : (center(M, K) & inc_c(P1, K) & midpoint(M, P1, P2) => circle_over(K, P1, P2))).
fof(circle_over_3, axiom, ![P1, P2, K, M] : (center(M, K) & inc_c(P2, K) & midpoint(M, P1, P2) => circle_over(K, P1, P2))).
fof(circle_over_inc, axiom, ![P1, P2, K] : (circle_over(K, P1, P2) & P1 != P2 => inc_c(P1, K) & inc_c(P2, K))).
fof(angle_over_diameter, axiom, ![P1, P2, X, L1, L2, K] : (X != P1 & X != P2 & P1 != P2 & circle_over(K, P1, P2) & inc_c(X, K) & line(P1, X, L1) & line(P2, X, L2) => perp(L1, L2))).
fof(distinct_ABC, axiom, pA != pB & pA != pC & pB != pC).
fof(inc_A_C_ac, axiom, inc(pA, ac) & inc(pC, ac)).
fof(inc_B_C_bc, axiom, inc(pB, bc) & inc(pC, bc)).
fof(inc_A_B_ab, axiom, inc(pA, ab) & inc(pB, ab)).
fof(perp_ha_BC, axiom, perp(ha, bc) & inc(pA, ha)).
fof(perp_hb_AC, axiom, perp(hb, ac) & inc(pB, hb)).
fof(perp_hc_AB, axiom, perp(hc, ab) & inc(pC, hc)).
fof(inc_Ha_ha, axiom, inc(pHa, ha) & inc(pHa, bc)).
fof(inc_Hb_hb, axiom, inc(pHb, hb) & inc(pHb, ac)).
fof(inc_Hc_hc, axiom, inc(pHc, hc) & inc(pHc, ab)).
fof(pMa_def, axiom, midpoint(pMa, pB, pC)).
fof(pMb_def, axiom, midpoint(pMb, pA, pC)).
fof(pMc_def, axiom, midpoint(pMc, pA, pB)).
fof(inc_cc, axiom, inc_c(pA, cc) & inc_c(pB, cc) & inc_c(pC, cc)).
fof(pOc_def, axiom, center(pOc, cc)).
fof(inc_Ma_bisa, axiom, inc(pMa, bisa)).
fof(inc_Mb_bisb, axiom, inc(pMb, bisb)).
fof(inc_Mc_bisc, axiom, inc(pMc, bisc)).
fof(perp_bisa_bc, axiom, perp(bisa, bc)).
fof(perp_bisb_ac, axiom, perp(bisb, ac)).
fof(perp_bisc_ab, axiom, perp(bisc, ab)).
fof(inc_Oc_bisa, axiom, inc(pOc, bisa)).
fof(inc_Oc_bisb, axiom, inc(pOc, bisb)).
fof(inc_Oc_bisc, axiom, inc(pOc, bisc)).
fof(inc_Hb_cBC, axiom, inc_c(pHb, cobc)).
fof(inc_Hc_cBC, axiom, inc_c(pHc, cobc)).
fof(inc_Ha_cAC, axiom, inc_c(pHa, coac)).
fof(inc_Hc_cAC, axiom, inc_c(pHc, coac)).
fof(inc_Ha_cAB, axiom, inc_c(pHa, coab)).
fof(inc_Hb_cAB, axiom, inc_c(pHb, coab)).
fof(ratio23_AGAMa, axiom, ratio23(pA, pG, pA, pMa)).
fof(ratio23_BGBMb, axiom, ratio23(pB, pG, pB, pMb)).
fof(ratio23_CGCMc, axiom, ratio23(pC, pG, pC, pMc)).
fof(ratio13_OGOH, axiom, ratio13(pOc, pG, pOc, pH)).
fof(unique_ratio13_1, axiom, ![A, B, X, Y] : (ratio13(A, X, A, B) & ratio13(A, Y, A, B) => X = Y)).
fof(unique_ratio13_2, axiom, ![A, B, X, Y] : (ratio13(A, B, A, X) & ratio13(A, B, A, Y) => X = Y)).
fof(unique_ratio31_1, axiom, ![A, B, X, Y] : (ratio31(A, X, A, B) & ratio31(A, Y, A, B) => X = Y)).
fof(unique_ratio31_2, axiom, ![A, B, X, Y] : (ratio31(A, B, A, X) & ratio31(A, B, A, Y) => X = Y)).
fof(unique_ratio23_1, axiom, ![A, B, X, Y] : (ratio23(A, X, A, B) & ratio23(A, Y, A, B) => X = Y)).
fof(unique_ratio23_2, axiom, ![A, B, X, Y] : (ratio23(A, B, A, X) & ratio23(A, B, A, Y) => X = Y)).
fof(unique_ratio32_1, axiom, ![A, B, X, Y] : (ratio32(A, X, A, B) & ratio32(A, Y, A, B) => X = Y)).
fof(unique_ratio32_2, axiom, ![A, B, X, Y] : (ratio32(A, B, A, X) & ratio32(A, B, A, Y) => X = Y)).
fof(unique_ratio12_1, axiom, ![A, B, X, Y] : (ratio12(A, X, A, B) & ratio12(A, Y, A, B) => X = Y)).
fof(unique_ratio12_2, axiom, ![A, B, X, Y] : (ratio12(A, B, A, X) & ratio12(A, B, A, Y) => X = Y)).
fof(unique_ratio21_1, axiom, ![A, B, X, Y] : (ratio21(A, X, A, B) & ratio21(A, Y, A, B) => X = Y)).
fof(unique_ratio21_2, axiom, ![A, B, X, Y] : (ratio21(A, B, A, X) & ratio21(A, B, A, Y) => X = Y)).
fof(unique_ratio12, axiom, ![A, B, X] : (ratio12(A, B, B, X) => ratio13(A, B, A, X))).
fof(unique_ratio21, axiom, ![A, B, X] : (ratio21(A, B, B, X) => ratio23(A, B, A, X))).
fof(ratio_converse_13, axiom, ![A, B, C] : (ratio13(A, B, B, C) => ratio31(C, B, B, A))).
fof(ratio_converse_31, axiom, ![A, B, C] : (ratio31(A, B, B, C) => ratio13(C, B, B, A))).
fof(ratio_converse_12, axiom, ![A, B, C] : (ratio12(A, B, B, C) => ratio21(C, B, B, A))).
fof(ratio_converse_21, axiom, ![A, B, C] : (ratio21(A, B, B, C) => ratio12(C, B, B, A))).
fof(ratio_converse_23, axiom, ![A, B, C] : (ratio23(A, B, B, C) => ratio32(C, B, B, A))).
fof(ratio_converse_32, axiom, ![A, B, C] : (ratio32(A, B, B, C) => ratio23(C, B, B, A))).
fof(unique_bisa, axiom, ![L] : (inc(pMa, L) & perp(L, bc) => L = bisa)).
fof(unique_bisb, axiom, ![L] : (inc(pMb, L) & perp(L, ac) => L = bisb)).
fof(unique_bisc, axiom, ![L] : (inc(pMc, L) & perp(L, ab) => L = bisc)).
fof(ratio21_AGGMa, axiom, ratio21(pA, pG, pG, pMa)).
fof(ratio21_BGGMb, axiom, ratio21(pB, pG, pG, pMb)).
fof(ratio21_CGGMc, axiom, ratio21(pC, pG, pG, pMc)).
fof(ratio23_Ma, axiom, ![X] : (ratio23(pA, pG, pA, X) => X = pMa)).
fof(ratio23_Mb, axiom, ![X] : (ratio23(pB, pG, pB, X) => X = pMb)).
fof(ratio23_Mc, axiom, ![X] : (ratio23(pC, pG, pC, X) => X = pMc)).
fof(ratio23_Ma_G, axiom, ![X] : (ratio23(pA, X, pA, pMa) => X = pG)).
fof(ratio23_Mb_G, axiom, ![X] : (ratio23(pB, X, pB, pMb) => X = pG)).
fof(ratio23_Mc_G, axiom, ![X] : (ratio23(pC, X, pC, pMc) => X = pG)).
fof(ratio21_Ma, axiom, ![X] : (ratio21(pA, pG, pG, X) => X = pMa)).
fof(ratio12_OGGH, axiom, ratio12(pOc, pG, pG, pH)).
fof(ratio23_ratio21, axiom, ![A, G, M] : (ratio23(A, G, A, M) => ratio21(A, G, G, M))).
fof(line_sym, axiom, ![P1, P2, L] : (P1 != P2 & line(P1, P2, L) => line(P2, P1, L))).
fof(sides, axiom, line(pA, pB, ab) & line(pA, pC, ac) & line(pB, pC, bc)).
fof(ab_unique, axiom, ![L] : (inc(pA, L) & inc(pB, L) => L = ab)).
fof(ac_unique, axiom, ![L] : (inc(pA, L) & inc(pC, L) => L = ac)).
fof(bc_unique, axiom, ![L] : (inc(pB, L) & inc(pC, L) => L = bc)).
fof(sides_distinct, axiom, ab != ac & ab != bc & ac != bc).
fof(altitudes_non_sides, axiom, ha != bc & hb != ac & hc != ab).
fof(pAHa, axiom, ![P] : (pA != pHa & line(pA, pHa, P) => P = ha)).
fof(pBHb, axiom, ![P] : (pB != pHb & line(pB, pHb, P) => P = hb)).
fof(pCHc, axiom, ![P] : (pC != pHc & line(pC, pHc, P) => P = hc)).
fof(haA, axiom, ![H] : (perp(H, bc) & inc(pA, H) => ha = H)).
fof(hbB, axiom, ![H] : (perp(H, ac) & inc(pB, H) => hb = H)).
fof(hcC, axiom, ![H] : (perp(H, ab) & inc(pC, H) => hc = H)).
fof(haHa, axiom, ![H] : (perp(H, bc) & inc(pHa, H) => ha = H)).
fof(hbHb, axiom, ![H] : (perp(H, ac) & inc(pHb, H) => hb = H)).
fof(hcHc, axiom, ![H] : (perp(H, ab) & inc(pHc, H) => hc = H)).
fof(circle_over_sym1, axiom, ![P1, P2, K1, K2] : (P1 != P2 & circle_over(K1, P1, P2) & circle_over(K2, P1, P2) => K1 = K2)).
fof(circle_over_sym2, axiom, ![P1, P2, K1] : (P1 != P2 & circle_over(K1, P1, P2) => circle_over(K1, P2, P1))).
fof(pHa_def, axiom, ![H1] : (inc(H1, ha) & inc(H1, bc) => H1 = pHa)).
fof(pHb_def, axiom, ![H1] : (inc(H1, hb) & inc(H1, ac) => H1 = pHb)).
fof(pHc_def, axiom, ![H1] : (inc(H1, hc) & inc(H1, ab) => H1 = pHc)).
fof(line_BHa, axiom, ![P, Q] : (pB != pHa & line(pB, pHa, P) & line(pB, pC, Q) => P = Q)).
fof(line_CHa, axiom, ![P, Q] : (pC != pHa & line(pC, pHa, P) & line(pB, pC, Q) => P = Q)).
fof(line_AHb, axiom, ![P, Q] : (pA != pHb & line(pA, pHb, P) & line(pA, pC, Q) => P = Q)).
fof(line_CHb, axiom, ![P, Q] : (pC != pHb & line(pC, pHb, P) & line(pA, pC, Q) => P = Q)).
fof(line_AHc, axiom, ![P, Q] : (pA != pHc & line(pA, pHc, P) & line(pA, pB, Q) => P = Q)).
fof(line_BHc, axiom, ![P, Q] : (pB != pHc & line(pB, pHc, P) & line(pA, pB, Q) => P = Q)).
fof(cc_unique, axiom, ![C] : (inc_c(pA, C) & inc_c(pB, C) & inc_c(pC, C) => C = cc)).
fof(oc_unique, axiom, ![C] : (inc_c(pA, C) & inc_c(pB, C) & inc_c(pC, C) & center(pO1, C) => pO1 = pOc)).
fof(inc_midpoint, axiom, ![X, Y, M, L] : (X != Y & midpoint(M, X, Y) & line(X, Y, L) => inc(M, L))).
fof(inc_Ma_bc, axiom, inc(pMa, bc)).
fof(inc_Mb_ac, axiom, inc(pMb, ac)).
fof(inc_Mc_ab, axiom, inc(pMc, ab)).
fof(perp_noteq, axiom, ![L1, L2] : (perp(L1, L2) => L1 != L2)).
fof(bisectors_not_sides, axiom, ab != bisc & ac != bisb & bc != bisa).
fof(pMa_is_intersect_bisa_bc, axiom, ![P] : (inc(P, bc) & inc(P, bisa) => P = pMa)).
fof(pMc_is_intersect_bisc_ab, axiom, ![P] : (inc(P, ab) & inc(P, bisc) => P = pMc)).
fof(pMb_is_intersect_bisb_ac, axiom, ![P] : (inc(P, ac) & inc(P, bisb) => P = pMb)).
fof(ratio21_para, axiom, ![A, G, Ma, H, Oc, Lba, Lha] : (ratio21(A, G, G, Ma) & ratio21(H, G, G, Oc) & line(Oc, Ma, Lba) & line(A, H, Lha) => para(Lba, Lha))).
fof(perp_para, axiom, ![Lba, Lha, A] : (perp(Lha, A) & para(Lba, Lha) => perp(Lba, A))).
fof(pH_def, axiom, inc(pH, ha) & inc(pH, hb) & inc(pH, hc)).
fof(pH_unique1, axiom, ![H1] : (inc(H1, ha) & inc(H1, hb) => H1 = pH)).
fof(pH_unique2, axiom, ![H1] : (inc(H1, ha) & inc(H1, hc) => H1 = pH)).
fof(pH_unique3, axiom, ![H1] : (inc(H1, hb) & inc(H1, hc) => H1 = pH)).

% CONJECTURE

%-----------------------
% lemma: A_O_Hb:
%-----------------------
%fof(th_A_O_Hb, conjecture, (inc(pA, b1) & inc(pHb1, b1) & inc_c(pA, k) & center(pO1, k) & inc_c(pC, k) & inc(pC, b1) & inc(pHb1, hb1) & perp(hb1, b1) & inc_c(pB, k) & inc(pB, hb1) => pHb = pHb1 & pO1 = pOc)).

%-----------------------
%lemma 305: O_G_Ha:
%-----------------------
%fof(th_O_G_Ha,conjecture, ( ( inc_c(pC,c) & inc_c(pB,c) & inc(pC,a1) & inc(pB,a1) & center(pO1,c) & inc_c(pA,c) & ratio13(pMa1,pG1,pMa1,pA) & inc(pMa1,a1) & inc(pMa1,ma1) & inc(pO1,ma1) & perp(a1,ma1) & inc(pHa1,a1) & perp(ha1,a1) & inc(pHa1,ha1) & inc(pH1,ha1) & ratio13(pO1,pG1,pO1,pH1)) => ( pO1=pOc & pG1=pG & pHa1=pHa) ) ).

%-----------------------
%lemma 281: O_Ma_H:
%-----------------------
%fof(th_O_Ma_H,conjecture, ( (ratio23(pH1,pG1,pH1,pOc1) & ratio23(pA,pG1,pA,pMa1) & inc(pMa1,m1) & inc(pOc1,m1) & center(pOc1,k1) & inc_c(pA,k1) & inc(pMa1,a1) & perp(a1,m1) & inc_c(pB,k1) & inc_c(pC,k1) & inc(pB,a1) & inc(pC,a1) & pA!=pH1) => (pMa1=pMa & pOc=pOc1) ) ).

%-----------------------
%lemma 315: O_Ha_H:
%-----------------------
fof(th_O_Ha_H,conjecture, ( (ratio23(pH1,pG1,pH1,pOc1) & inc(pHa1,ha1) & inc(pH1,ha1) & inc(pHa1,a1) & perp(a1,ha1) & inc(pOc1,ma1) & perp(ma1,a1) & inc(pMa1,ma1) & inc(pMa1,a1) & ratio23(pA,pG1,pA,pMa1) & center(pOc1,k1) & inc_c(pA,k1) & inc_c(pB,k1) & inc_c(pC,k1) & inc(pB,a1) & inc(pC,a1)) => (pOc1=pOc & pHa1=pHa & pH1=pH) ) ).
