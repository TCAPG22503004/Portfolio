import pygame
import time
import math

def main():

	# 初期設定
	pygame.init()
	screen = pygame.display.set_mode((1280, 720))
	pygame.display.set_caption("fly")
	clock = pygame.time.Clock()
	clock.tick(60)
	time.sleep(1)


	# テスト
	# https://mitani.cs.tsukuba.ac.jp/lecture/old2015/cg/03/03_slides.pdf
	fov = math.pi / 4
	distance = 640 / math.tan(fov / 2)

	player = [100, 100, 0, 1]
	rot = [0, 0, 0]
	dRot = [0.008, 0.004, 0.004]
	speed = 0.1

	opos = [100, 100, 1500]
	size = 100
	p = [
		[opos[0],      opos[1],      opos[2],      1],
		[opos[0]-size, opos[1],      opos[2],      1],
		[opos[0]-size, opos[1]-size, opos[2],      1],
		[opos[0],      opos[1]-size, opos[2],      1],
		[opos[0],      opos[1],      opos[2],      1],
		[opos[0],      opos[1],      opos[2]+size, 1],
		[opos[0],      opos[1]-size, opos[2]+size, 1],
		[opos[0],      opos[1]-size, opos[2],      1],
		[opos[0],      opos[1],      opos[2],      1],
		[opos[0],      opos[1],      opos[2]+size, 1],
		[opos[0]-size, opos[1],      opos[2]+size, 1],
		[opos[0]-size, opos[1],      opos[2],      1],

	]


	opos2 = [300, 200, 1600]
	p2 = [
		[opos2[0],      opos2[1],      opos2[2],      1],
		[opos2[0]-size, opos2[1],      opos2[2],      1],
		[opos2[0]-size, opos2[1]-size, opos2[2],      1],
		[opos2[0],      opos2[1]-size, opos2[2],      1],
		[opos2[0],      opos2[1],      opos2[2],      1],
		[opos2[0],      opos2[1],      opos2[2]+size, 1],
		[opos2[0],      opos2[1]-size, opos2[2]+size, 1],
		[opos2[0],      opos2[1]-size, opos2[2],      1],
		[opos2[0],      opos2[1],      opos2[2],      1],
		[opos2[0],      opos2[1],      opos2[2]+size, 1],
		[opos2[0]-size, opos2[1],      opos2[2]+size, 1],
		[opos2[0]-size, opos2[1],      opos2[2],      1],

	]

	isRoop = True
	while(isRoop):

		# プレイヤーの移動
		dPos = Matrix([[0, 0, speed, 1]], rot, [0, 0, 0, 1])
		for i in range(3):
			player[i] += dPos[0][i]

		# 図形の描画
		q = Matrix(p, [-rot[0], -rot[1], -rot[2]], player)
		q2 = Matrix(p2, [-rot[0], -rot[1], -rot[2]], player)
		vertex = []
		vertex2 = []
		isDraw = [True, True]
		for i in range(len(q)):
			if q[i][2] > -distance:
				x = distance * q[i][0] / (distance + q[i][2]) + 640
				y = distance * q[i][1] / (distance + q[i][2]) * -1 + 360
				vertex.append([x, y])
			else:
				isDraw[0] = False

			if q2[i][2] > -distance:
				x = distance * q2[i][0] / (distance + q2[i][2]) + 640
				y = distance * q2[i][1] / (distance + q2[i][2]) * -1 + 360
				vertex2.append([x, y])
			else:
				isDraw[1] = False

		screen.fill((0, 0, 0))
		if isDraw[0]: pygame.draw.polygon(screen, (255, 0, 0), vertex, width=5)
		if isDraw[1]: pygame.draw.polygon(screen, (0, 255, 0), vertex2, width=5)
		pygame.draw.circle(screen, (0, 0, 255), (640, 360), 5)
		pygame.display.flip()


		# キー入力
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				isRoop = False
		keys = pygame.key.get_pressed()		
		if keys[pygame.K_e]:
			rot[0] += dRot[0]
		if keys[pygame.K_q]:
			rot[0] -= dRot[0]
		if keys[pygame.K_w]:
			rot[1] -= dRot[1]
		if keys[pygame.K_s]:
			rot[1] += dRot[1]
		if keys[pygame.K_d]:
			rot[2] += dRot[2]
		if keys[pygame.K_a]:
			rot[2] -= dRot[2]
		if keys[pygame.K_ESCAPE]:
			pygame.quit()
			isRoop = False				

#		print(["{:.3f}".format(rot[0]), "{:.3f}".format(rot[1]), "{:.3f}".format(rot[2])])
	return

def Matrix(a: list, b: list, c: list):

	newList = []

	mMove = [
		[1, 0, 0, -c[0]],
		[0, 1, 0, -c[1]],
		[0, 0, 1, -c[2]],
		[0, 0, 0, 1],
	]
	mMoveInverse = [
		[1, 0, 0, c[0]],
		[0, 1, 0, c[1]],
		[0, 0, 1, c[2]],
		[0, 0, 0, 1],
	]
	mRotRoll = [
		[math.cos(b[0]), -math.sin(b[0]), 0, 0],
		[math.sin(b[0]),  math.cos(b[0]), 0, 0],
		[             0,               0, 1, 0],
		[             0,               0, 0, 1],
	]

	mRotPitch = [
		[1,              0,               0, 0],
		[0, math.cos(b[1]), -math.sin(b[1]), 0],
		[0, math.sin(b[1]),  math.cos(b[1]), 0],
		[0,              0,               0, 1],
	]

	mRotYaw = [
		[ math.cos(b[2]), 0, math.sin(b[2]), 0],
		[              0, 1,              0, 0],
		[-math.sin(b[2]), 0, math.cos(b[2]), 0],
		[              0, 0,              0, 1],
	]

	for m in a:
		
		n = calc(m, mMove)

#		n = calc(n, mRotRoll)
#		n = calc(n, mRotPitch)
		n = calc(n, mRotYaw)
		n = calc(n, mRotPitch)
#		n = calc(n, mRotRoll)

#		n = calc(n, mMoveInverse)
		newList.append(n)

	return newList


def calc(xyz: list, d: list):

	newList = []

	for i in range(4):
		s = 0
		for j in range(4):
			s += d[i][j] * xyz[j]
		newList.append(s)

	return newList


if __name__ == "__main__":
	main()
