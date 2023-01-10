The Wasserstein distance has its roots in forming a metric between two probability measures. 

Sliced-Wasserstein distance has significantly lower computational requirements than the classical Wasserstein distance.

GSW(generalized sliced-Wasserstein) distance can be extended to a maximum GSW (max-GSW) distance.

Sliced-Wasserstein distance is calculated via linear slicing of the probability distributions.

- First, obtain a family of one-dimensional representations for a higher- dimensional probability distribution through linear projections (via the Radon transform).

- Then, calculate the distance between two input distributions as a functional on the p-Wasserstein distance of their one-dimensional representations (i.e., the one-dimensional marginals). 

- The sliced p-Wasserstein distance between Iμ and Iv is then formally defined as:
$$\[S W_{p}\left(I_{\mu}, I_{\nu}\right)=\left(\int_{\mathbb{S}^{d-1}} W_{p}^{p}\left(\mathcal{R} I_{\mu}(., \theta), \mathcal{R} I_{\nu}(., \theta)\right) d \theta\right)^{\frac{1}{p}}\]$$

- The computation of the SW distance requires an integration over the unit sphere in Rd. This integration is approximated by using a simple Monte Carlo scheme replaces the integral with a finite-sample average:
$$\[S W_{p}\left(I_{\mu}, I_{\nu}\right) \approx\left(\frac{1}{L} \sum_{l=1}^{L} W_{p}^{p}\left(\mathcal{R} I_{\mu}\left(\cdot, \theta_{l}\right), \mathcal{R} I_{\nu}\left(\cdot, \theta_{l}\right)\right)\right)^{1 / p}\]$$

-Alternative OT metric for maximum sliced p-Wasserstein:
$$\[\max -S W_{p}\left(I_{\mu}, I_{\nu}\right)=\max _{\theta \in \mathbb{S}^{d-1}} W_{p}\left(\mathcal{R} I_{\mu}(\cdot, \theta), \mathcal{R} I_{\nu}(\cdot, \theta)\right)\]$$

