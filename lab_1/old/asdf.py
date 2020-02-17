import matplotlib.pyplot as plt


length = [2, 3, 4, 5, 6, 7]
lev_tab = [1.24e-05, 1.86e-05, 3.22e-05, 4.20e-05, 6.38e-05, 8.64e-05]
dam_lev_tab = [1.43e-05, 2.29e-05, 3.37e-05, 4.94e-05, 7.42e-05, 1.01e-04]
dam_lev_rec = [1.83e-05, 9.10e-05, 4.95e-04, 2.75e-03, 1.60e-02, 8.83e-02]



plt.plot(length, lev_tab, 'r', label="lev_tab")
plt.plot(length, dam_lev_tab, 'b', label="dam_lev_tab")
plt.legend(loc='upper left')
plt.axis([2, 7, min(lev_tab + dam_lev_tab), max(lev_tab + dam_lev_tab)])
plt.grid(True)
plt.show()

plt.plot(length, dam_lev_rec, 'g', label="dam_lev_rec")
plt.plot(length, dam_lev_tab, 'b', label="dam_lev_tab")
plt.legend(loc='upper left')
plt.axis([2, 7, min(dam_lev_tab + dam_lev_rec), max(dam_lev_tab + dam_lev_rec)])
plt.grid(True)
plt.show()

