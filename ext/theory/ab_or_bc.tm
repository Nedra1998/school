q0,2->q20,_,R
q20,_->qaccept,_,R
q20,2->q20,_,R
q0,1->q10,_,R
q10,1->q10,1,R
q10,2->q10,2,R
q10,X->q10,X,R
q10,_->q11,_,L
q11,2->q12,_,L
q12,1->q12,1,L
q12,2->q12,2,L
q12,X->q12,X,L
q12,_->q13,_,R
q13,1->q10,_,R
q13,X->q10,_,R
q13,_->qaccept,_,R
q0,0->q00,_,R
q00,0->q00,0,R
q00,1->q00,1,R
q00,2->q01,2,L
q00,X->q01,X,L
q00,_->q01,_,L
q01,1->q02,X,L
q01,0->q04,_,R
q02,0->q02,0,L
q02,1->q02,1,L
q02,_->q03,_,R
q03,0->q00,_,R
q03,X->qaccept,X,R
q03,1->q10,_,R
q04,X->q10,_,R
