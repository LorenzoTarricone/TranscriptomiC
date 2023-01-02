Spatial transcriptomics at subspot resolution with BayesSpace

https://www.nature.com/articles/s41587-021-00935-2

- Introduce BayesSpace, a fully Bayesian statistical method that uses the information from spatial neighborhoods for resolution enhancement 
of spatial transcriptomic data and for clustering analysis.

- BayesSpace enhanced-resolution clustering can increase the resolution of data that were simulated from real, aggregated single cells.

- BayesSpace enhanced-resolution clustering outperformed the optimal clustering that can be achieved at the spot level in melanoma and 
ovarian samples that were simulated at the subspot level.

- Data modelling: 
 $$\left( {y_i{\mathrm{|}}z_i = k,w_i} \right) \sim N\left( {y_i;\mu _k,w_i^{ - 1}{\Lambda}^{ - 1}} \right)$$
denotes the latent cluster that i belongs to, μk denotes the mean vector for cluster k, Λ denotes the precision matrix, and wi denotes an unknown (observation-specific) scaling factor.

- Assume a common (fixed) precision matrix across clusters because the number of unknown parameters in the precision matrix quickly rises with higher numbers of 
clusters and numbers of PCs modeled.

- Assume that the common precision matrix is unconstrained as there is correlation between PCs after conditioning on cluster, even though PCs are marginally 
uncorrelated.

- The variable precision model often required strong priors for parameter estimation.

- The number of clusters q is determined by prior biological knowledge when available or otherwise by the elbow of the pseudo-log-likelihood plot.

- Place the following priors on μk, Λ and wi, 
$$\mu _k\mathop{\sim}\limits^{\textrm{i.i.d.}} N\left( {\mu _0,{\Lambda}_0^{ - 1}} \right),\\$$ 
$${\Lambda}\mathop{\sim}\limits^{{\textrm{i.i.d.}}}\textrm{Wishart}_d\left( {\alpha ,{\textrm{diag}}\left( \beta \right)_d^{ - 1}} \right),\\$$ 
$$w_i\mathop{\sim}\limits^{\textrm{i.i.d.}}\Gamma\left( {\frac{\nu }{2},\frac{\nu }{2}} \right),||$$
where μ0, Λ0, α and β are fixed hyperparameters. By default, we set μ0 to be the empirical mean vector of the data.

- Iteratively and sequentially, each μk, Λ and wi is updated via Gibbs sampling, and each zi is updated via the Metropolis–Hastings algorithm. Each zi is updated by taking into account both the likelihood and spatial prior information.
The Markov random field prior is given by the Potts model:
$$\pi \left( {z_i} \right) = \exp \left( {\frac{\gamma }{{\left| {\left\langle {ij} \right\rangle } \right|}} \times 2\mathop {\sum }\limits_{\left\langle {ij} \right\rangle } I\left( {z_i = z_j} \right)} \right)$$,
where $\left\langle {i\,j} \right\rangle$ denotes all spots j that are neighbors of i, I represents the indicator function, and γ is a fixed parameter controlling the strength of the smoothing.
