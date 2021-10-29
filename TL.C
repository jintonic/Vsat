{
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.01);

	// data, hole, Reggiani, PRB 16 (1977) 2781 
	const int n = 7;
	float vh100[n] = {1.21, 1.20, 1.16, 1.13, 0.98, 0.82, 0.76};
	float dvh[n] = {0.057, 0.059, 0.046, 0.052, 0.048, 0.034, 0.036};
	float th[n] = {8, 20, 40, 77, 130, 190, 220}, dt[n]={0};
	TGraphErrors *gh = new TGraphErrors(n, th, vh100, dt, dvh);

	// data, electron, Jacoboni, PRB 24 (1981) 1014
	float ve100[n+1] = {1.9, 1.5, 1.2, 1.1, 1.05, 0.9, 0.82, 0.62};
	float dve[n+1] = {0.057, 0.059, 0.046, 0.052, 0.048, 0.034, 0.036, 0.036};
	float te[n+1] = {8, 20, 45, 77, 130, 190, 240, 300};
	TGraphErrors *ge = new TGraphErrors(n+1, te, ve100, dt, dve);

	// model, Quay, Mat. Sci. Semi. Proc. 3 (2000) 149
	TF1 *f = new TF1 ("f", "[0]/(1-[1]+[1]*x/300)", 0, 330);
	f->SetParNames("Vsat300", "A");

	TF1 *fe = (TF1*) f->Clone("fe");
	TF1 *fh = (TF1*) f->Clone("fh");

	// draw
	ge->GetXaxis()->SetRangeUser(0,320);
	ge->GetYaxis()->SetRangeUser(0.55,2.05);
	ge->SetTitle(";Temperature [K]; V_{sat} along #LT 100 #GT [10^{7} cm/s]");
	ge->SetMarkerStyle(20);
	ge->Draw("ap");
	gh->SetMarkerStyle(21);
	gh->Draw("p");

	fe->SetLineColor(kRed);
	fh->SetLineColor(kBlue);

	fe->SetParameters(0.70, 0.45);
	fh->SetParameters(0.63, 0.39);

	fe->Draw("same");
	fh->Draw("same");

	TLegend *l = new TLegend(0.6, 0.7, 0.98, 0.98);
	l->AddEntry(gh, "Hole (data)", "p");
	l->AddEntry(ge, "Electron (data)", "p");
	l->AddEntry(fh, "Hole (model)", "l");
	l->AddEntry(fe, "Electron (model)", "l");
	l->Draw();
}
