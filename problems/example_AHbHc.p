% AXIOMS

fof(line_unique, axiom, ![P1, P2, L1, L2] : (line(P1, P2, L1) & line(P1, P2, L2) & P1 != P2 => L1 = L2)).
fof(line_inc, axiom, ![P1, P2, L] : (line(P1, P2, L) => inc(P1, L) & inc(P2, L))).
fof(inc_line, axiom, ![P1, P2, L] : (inc(P1, L) & inc(P2, L) & P1 != P2 => line(P1, P2, L))).
%fof(ex_line, axiom, ![P1, P2] : (? [L] : line(P1, P2, L))).
fof(intersect_unique, axiom, ![P1, P2, L1, L2] : (L1 != L2 & inc(P1, L1) & inc(P1, L2) & inc(P2, L1) & inc(P2, L2) => P1 = P2)).
fof(intersect_unique2, axiom, ![P1, P2, P3, L1, C1] : (inc(P1, L1) & inc_c(P1, C1) & inc(P2, L1) & inc_c(P2, C1) & inc_c(P3, C1) & inc(P3, L1) & P1 != P2 & P1 != P3 => P2 = P3)).
fof(intersect_unique3, axiom, ![P1, P2, P3, C1, C2] : (C1 != C2 & inc_c(P1, C1) & inc_c(P2, C1) & inc_c(P3, C1) & inc_c(P1, C2) & inc_c(P2, C2) & inc_c(P3, C2) & P1 != P2 & P1 != P3 => P2 = P3)).
fof(perp_sym, axiom, ![L1, L2] : (perp(L1, L2) => perp(L2, L1))).
fof(perp_unique, axiom, ![P, L, L1, L2] : (perp(L1, L) & inc(P, L1) & perp(L2, L) & inc(P, L2) => L1 = L2)).
fof(circle_center, axiom, ![K, Pc, Px] : (circle(K, Pc, Px) => center(Pc, K))).
fof(circle_point, axiom, ![K, Pc, Px] : (circle(K, Pc, Px) => inc_c(Px, K))).
fof(circle_def, axiom, ![K, Pc, Px] : (Pc != Px & center(Pc, K) & inc_c(Px, K) => circle(K, Pc, Px))).
fof(center_unique, axiom, ![C, C1, C2] : (center(C1, C) & center(C2, C) => C1 = C2)).
fof(circle_unique, axiom, ![O, P, C1, C2] : (center(O, C1) & center(O, C2) & inc_c(P, C1) & inc_c(P, C2) => C1 = C2)).
fof(circle3, axiom, ![P1, P2, P3, C1, C2] : (P1 != P2 & P1 != P3 & P2 != P3 & inc_c(P1, C1) & inc_c(P2, C1) & inc_c(P3, C1) & inc_c(P1, C2) & inc_c(P2, C2) & inc_c(P3, C2) => C1 = C2)).
fof(para_sym, axiom, ![A, B] : (para(A, B) => para(B, A))).
fof(circle_over_1, axiom, ![P1, P2, K, M] : (circle_over(K, P1, P2) & midpoint(M, P1, P2) => center(M, K) & inc_c(P1, K) & inc_c(P2, K))).
fof(circle_over_2, axiom, ![P1, P2, K, M] : (center(M, K) & inc_c(P1, K) & midpoint(M, P1, P2) => circle_over(K, P1, P2))).
fof(circle_over_3, axiom, ![P1, P2, K, M] : (center(M, K) & inc_c(P2, K) & midpoint(M, P1, P2) => circle_over(K, P1, P2))).
fof(circle_over_inc, axiom, ![P1, P2, K] : (circle_over(K, P1, P2) & P1 != P2 => inc_c(P1, K) & inc_c(P2, K))).
fof(angle_over_diameter, axiom, ![P1, P2, X, L1, L2, K] : (X != P1 & X != P2 & P1 != P2 & circle_over(K, P1, P2) & inc_c(X, K) & line(P1, X, L1) & line(P2, X, L2) => perp(L1, L2))).
fof(distinct_ABC, axiom, pA != pB & pA != pC & pB != pC).
%fof(colinear_def, axiom, ![A, B, C] : (colinear(A, B, C) => ?[L] : (inc(A, L) & inc(B, L) & inc(C, L)))).
fof(non_colinear_ABC, axiom, ~colinear(pA, pB, pC)).
fof(line_eq_colinear1, axiom, ![A, B, C, D, L1, L2] : (A != B & C != D & line(A, B, L1) & line(C, D, L2) & L1 = L2 => colinear(A, B, C) & colinear(A, B, D))).
fof(colinear_cycle, axiom, ![A, B, C] : (colinear(A, B, C) => colinear(B, C, A))).
fof(colinear_sym, axiom, ![A, B, C] : (colinear(A, B, C) => colinear(B, A, C))).
fof(inc_A_C_ac, axiom, inc(pA, ac) & inc(pC, ac)).
fof(inc_B_C_bc, axiom, inc(pB, bc) & inc(pC, bc)).
fof(inc_A_B_ab, axiom, inc(pA, ab) & inc(pB, ab)).
fof(perp_ha_BC, axiom, perp(ha, bc) & inc(pA, ha)).
fof(perp_hb_AC, axiom, perp(hb, ac) & inc(pB, hb)).
fof(perp_hc_AB, axiom, perp(hc, ab) & inc(pC, hc)).
fof(inc_Ha_ha, axiom, inc(pHa, ha) & inc(pHa, bc)).
fof(inc_Hb_hb, axiom, inc(pHb, hb) & inc(pHb, ac)).
fof(inc_Hc_hc, axiom, inc(pHc, hc) & inc(pHc, ab)).
fof(inc_cc, axiom, inc_c(pA, cc) & inc_c(pB, cc) & inc_c(pC, cc)).
fof(pOc_def, axiom, center(pOc, cc)).
fof(coab_def, axiom, circle_over(coab, pA, pB)).
fof(cobc_def, axiom, circle_over(cobc, pB, pC)).
fof(coac_def, axiom, circle_over(coac, pA, pC)).
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
fof(perp_noteq, axiom, ![L1, L2] : (perp(L1, L2) => L1 != L2)).
fof(bisectors_not_sides, axiom, ab != bisc & ac != bisb & bc != bisa).
fof(perp_para, axiom, ![Lba, Lha, A] : (perp(Lha, A) & para(Lba, Lha) => perp(Lba, A))).
fof(pH_def, axiom, inc(pH, ha) & inc(pH, hb) & inc(pH, hc)).
fof(pH_unique1, axiom, ![H1] : (inc(H1, ha) & inc(H1, hb) => H1 = pH)).
fof(pH_unique2, axiom, ![H1] : (inc(H1, ha) & inc(H1, hc) => H1 = pH)).
fof(pH_unique3, axiom, ![H1] : (inc(H1, hb) & inc(H1, hc) => H1 = pH)).

% CONJECTURE

%-----------------------
% lemma: A_Hb_Hc:
%-----------------------
fof(th_A_Hb_Hc, conjecture, inc(pA, b1) & inc(pHb1, b1) & inc(pA, c1) & inc(pHc1, c1) & perp(hb1, b1) & inc(pHb1, hb1) & perp(hc1, c1) & inc(pHc1, hc1) & inc(pB, hb1) & inc(pB, c1) & inc(pC, hc1) & inc(pC, b1) => pHb = pHb1 & pHc = pHc1).

