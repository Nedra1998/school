q0,a->q1,X,L
q0,_->qaccept,_,R
q1,a->q1,a,L
q1,_->q2,_,L
q2,1->q2,0,L
q2,0->q3,1,R
q2,_->q3,1,R
q3,0->q3,0,R
q3,1->q3,1,R
q3,_->q4,_,R
q4,a->q4,a,R
q4,_->qaccept,_,L
q4,X->q0,X,L
