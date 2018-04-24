import os
import numpy as np
import time
from magenta.models.nsynth import utils
from magenta.models.nsynth.wavenet import fastgen
from scipy import signal
CUDA_VISIBLE_DEVICES=""
sample_length  = 512


encoding_sine = np.load('wavetable_sine.npy')
encoding_tri = np.load('wavetable_tri.npy')
encoding_saw = np.load('wavetable_saw.npy')

#sawsin
for i in range(1,100):
	filename = '../prerender/SawSin/SawSin_0.' + '%02d.txt' % i
	time0 = time.time()
	print('decoding saw+sine interpolation:'+ '%02d' % i)
	fastgen.synthesize((encoding_saw * (100-i) + encoding_sine * i)/100, save_paths=['tmp'], checkpoint_path='Model/wavenet-ckpt/model.ckpt-200000', samples_per_save=sample_length)
	audio = utils.load_audio('tmp', sample_length=512, sr=16000)
	np.savetxt(filename,[np.around(audio, decimals=5)],delimiter=',',fmt='%1.5f')
	print(time.time()-time0)

#sintri
for i in range(1,100):
	filename = '../prerender/SinTri/SinTri_0.' + '%02d.txt' % i
	time0 = time.time()
	print('decoding sine+tri interpolation:' + '%02d' % i)
	fastgen.synthesize((encoding_sine * (100-i) + encoding_tri * i)/100, save_paths=['tmp'], checkpoint_path='Model/wavenet-ckpt/model.ckpt-200000', samples_per_save=sample_length)
	audio = utils.load_audio('tmp', sample_length=512, sr=16000)
	np.savetxt(filename,[np.around(audio, decimals=5)],delimiter=',',fmt='%1.5f')
	print(time.time()-time0)

#trisaw
for i in range(1,100):
	filename = '../prerender/TriSaw/TriSaw_0.' + '%02d.txt' % i
	time0 = time.time()
	print('decoding tri+saw interpolation:'+ '%02d' % i)
	fastgen.synthesize((encoding_tri * (100-i) + encoding_saw * i)/100, save_paths=['tmp'], checkpoint_path='Model/wavenet-ckpt/model.ckpt-200000', samples_per_save=sample_length)
	audio = utils.load_audio('tmp', sample_length=512, sr=16000)
	np.savetxt(filename,[np.around(audio, decimals=5)],delimiter=',',fmt='%1.5f')
	print(time.time()-time0)
