{
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.01);

	// data, hole, Reggiani, PRB 16 (1977) 2781 
	const int n = 7;
	float vs100[n] = {1.21, 1.20, 1.16, 1.13, 0.98, 0.82, 0.76};
	float dvs[n] = {0.057, 0.059, 0.046, 0.052, 0.048, 0.034, 0.036};
	float tl[n] = {8, 20, 40, 77, 130, 190, 220}, dt[n]={0};
	TGraphErrors *gh = new TGraphErrors(n, tl, vs100, dt, dvs);

	// model, Quay, Mat. Sci. Semi. Proc. 3 (2000) 149
	TF1 *f = new TF1 ("f", "[0]/(1-[1]+[1]*x/300)", 0, 330);
	f->SetParNames("Vsat300", "A");

	TF1 *fe = (TF1*) f->Clone("fe");
	TF1 *fh = (TF1*) f->Clone("fh");

	// draw
	gh->GetXaxis()->SetRangeUser(0,290);
	gh->GetYaxis()->SetRangeUser(0.65,1.35);
	gh->SetTitle(";Temperature [K]; V_{sat} [10^{7} cm/s]");
	gh->SetMarkerStyle(20);
	gh->Draw("ap");

	fe->SetLineColor(kRed);
	fh->SetLineColor(kBlue);

	fe->SetParameters(0.72, 0.45);
	fh->SetParameters(0.63, 0.39);

	fe->Draw("same");
	fh->Draw("same");

	TLegend *l = new TLegend(0.6, 0.7, 0.98, 0.98);
	l->AddEntry(gh, "Hole (data)", "p");
	l->AddEntry(fe, "Electron (model)", "l");
	l->AddEntry(fh, "Hole (model)", "l");
	l->Draw();
}
