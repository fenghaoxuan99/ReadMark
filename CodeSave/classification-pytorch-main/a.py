from tqdm import tqdm

# assume
dataset_num = 100000
batch_size = 8
epoch = 1
d_loss = 1.2345
g_loss = 1.2345

pbar = tqdm(range(int(dataset_num / batch_size)))

for i in pbar:
    epoch += 1
    d_loss += 1.2345
    g_loss += 1.2345
    pbar.set_description('Epoch: %i' % epoch)
    pbar.set_postfix(d_loss=format(d_loss,'.3f'), g_loss=format(g_loss,'.3f'))
