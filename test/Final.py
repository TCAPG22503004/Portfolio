import pygame
import time
import math
import random

def main():

	# 初期設定
	pygame.init()
	screen = pygame.display.set_mode((1280, 720))
	pygame.display.set_caption("fly")
	clock = pygame.time.Clock()
	clock.tick(60)
	font = pygame.font.SysFont(None, 64)
	time.sleep(1)


	# テスト
	# https://mitani.cs.tsukuba.ac.jp/lecture/old2015/cg/03/03_slides.pdf
	player = [0, 0, 0]
	speed = 3

	fov = math.pi / 4
	distance = 640 / math.tan(fov / 2)

	rot = [1, 0, 0, 0]
	rot2 = [1, 0, 0, 0]
	dRot = 0.001

	orthorhombic = []
	limit = 10
	for i in range(limit):
		orthorhombic.append(makeOrthoRandom())

	isRoop = True
	while(isRoop):

		# 移動
		dv = Rotation([0, 0, 1], rot2, [0, 0, 0])
		for i in range(3):
			player[i] += dv[i] * speed

		# 回転
		drawList = []
		i = -1
		for xyz in orthorhombic:
			
			vertex = xyz[2]
			drawList.append([])
			i += 1
			for xyz2 in vertex:
				newDrawList = Rotation(xyz2, rot, player)
				drawList[i].append(newDrawList)

		vertex = []
		isDraw = [False] * limit
		invisible = []

		# 座標の計算
		for i in range(len(drawList)):
			vertex.append([])
			for xyz in drawList[i]:
				if xyz[2] > 0:
					x = distance * xyz[0] / xyz[2] + 640
					y = distance * xyz[1] / xyz[2] * -1 + 360
					vertex[i].append([x, y])
					threshold = 251
					if (x >= 0 - threshold and x <= 1280 + threshold) and (y >= 0 - threshold and y <= 720 + threshold): isDraw[i] = True

			# 見切れたかの判定
			if isDraw[i] == False:

				# 見切れた方向の反対側に生成する
				ap = [0, 0]
				if x < 0 - threshold:
					ap[0] = 1
				elif x > 1280 + threshold:
					ap[0] = -1
				if y < 0 - threshold:
					ap[1] = 1
				elif y > 720 + threshold:
					ap[1] = -1
				invisible.append(ap)


		# 描画
		screen.fill((0, 0, 0))

		for i in range(len(vertex)):
			if isDraw[i]: pygame.draw.polygon(screen, (255, 255, 255), vertex[i], width=5)

#		txt = ""
#		for i in range(4):
#			txt += "{:.4f}, ".format(rot2[i])
#		screen.blit(font.render(txt, False, (255, 255, 255)), (0, 720-64))

		pygame.display.flip()


		# 非表示になった立体を消す
		newOrthoList = []
		for i in range(limit):
			if (isDraw[i]):
				newOrthoList.append(orthorhombic[i])

		# 補充
		for s in invisible:
			newOrthoList.append(makeOrtho(player, rot2, s))

		orthorhombic = newOrthoList


		# キー入力
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				isRoop = False
		keys = pygame.key.get_pressed()		
		if keys[pygame.K_w]:
			rot = SetRotate(rot, dRot, 0)
			rot2 = SetRotate2(rot2, -dRot, 0)
		if keys[pygame.K_s]:
			rot = SetRotate(rot, -dRot, 0)
			rot2 = SetRotate2(rot2, dRot, 0)
		if keys[pygame.K_a]:
			rot = SetRotate(rot, dRot, 1)
			rot2 = SetRotate2(rot2, -dRot, 1)
		if keys[pygame.K_d]:
			rot = SetRotate(rot, -dRot, 1)
			rot2 = SetRotate2(rot2, dRot, 1)
		if keys[pygame.K_q]:
			rot = SetRotate(rot, dRot, 2)
			rot2 = SetRotate2(rot2, -dRot, 2)
		if keys[pygame.K_e]:
			rot = SetRotate(rot, -dRot, 2)
			rot2 = SetRotate2(rot2, dRot, 2)
		if keys[pygame.K_r]:
			rot = [1, 0, 0, 0]
			rot2 = [1, 0, 0, 0]
			player = [0, 0, 0]
			orthorhombic = []
			for i in range(limit):
				orthorhombic.append(makeOrthoRandom())
		if keys[pygame.K_ESCAPE]:
			pygame.quit()
			isRoop = False				
	return

def Rotation(pos: list, rot: list, player: list):

	newList = calc(rot, [1, pos[0]-player[0], pos[1]-player[1], pos[2]-player[2]])
	rotConjugate = [rot[0], -rot[1], -rot[2], -rot[3]]
	newList = calc(newList, rotConjugate)

	return newList[1:]
	

def SetRotate(before: list, delta: float, n: int):
	r = [math.cos(delta), 0, 0, 0]
	r[n+1] = math.sin(delta)

	return calc(r, before)


def SetRotate2(before: list, delta: float, n: int):
	r = [math.cos(delta), 0, 0, 0]
	r[n+1] = math.sin(delta)

	return calc(before, r)


def calc(left:list, right:list):

	l2 = makeMatrix(left)
	newList = []

	for i in range(4):
		s = 0
		for j in range(4):
			s += l2[i][j] * right[j]
		newList.append(s)
	
	return newList

def makeMatrix(a: list):
	return [
		[a[0], -a[1], -a[2], -a[3]],
		[a[1],  a[0], -a[3],  a[2]],
		[a[2],  a[3],  a[0], -a[1]],
		[a[3], -a[2],  a[1],  a[0]]
	]

def makeVertex(o: list, d: list):

	ox = o[0]
	oy = o[1]
	oz = o[2]
	dx = d[0] / 2
	dy = d[1] / 2
	dz = d[2] / 2

	return [
		[ox-dx, oy+dy, oz-dz],
		[ox-dx, oy-dy, oz-dz],
		[ox+dx, oy-dy, oz-dz],
		[ox+dx, oy-dy, oz+dz],
		[ox+dx, oy+dy, oz+dz],
		[ox-dx, oy+dy, oz+dz],
		[ox-dx, oy+dy, oz-dz],
		[ox+dx, oy+dy, oz-dz],
		[ox+dx, oy+dy, oz+dz],
		[ox+dx, oy+dy, oz-dz],
		[ox+dx, oy-dy, oz-dz],
		[ox+dx, oy-dy, oz+dz],
		[ox-dx, oy-dy, oz+dz],
		[ox-dx, oy-dy, oz-dz],
		[ox-dx, oy-dy, oz+dz],
		[ox-dx, oy+dy, oz+dz],
	]


def makeOrtho(p: list, r: list, di: list):

	d1 = math.pi / 4 / 2 / 2 * 1.2
	d2 = d1 * 720 / 1280 * 1.1
	if di[0] != 0:
		theta1 = di[0] * d1
	else:
		d = 0.8
		theta1 = random.uniform(-d1*d, d1*d)
	if di[1] != 0:
		theta2 = di[1] * d2
	else:
		d = 0.8
		theta2 = random.uniform(-d2*d, d2*d)
	
	randRot = SetRotate2(r, theta1, 1)
	randRot = SetRotate2(randRot, theta2, 0)

	direction = Rotation([0, 0, random.randint(5000, 10000)], randRot, [0, 0, 0])
	a = []
	for i in range(3):
		a.append(p[i] + direction[i])

	center = []
	delta = []
	for i in range(3):
		center.append(a[i])
		delta.append(random.randint(100, 500))

	return [center, delta, makeVertex(center, delta)]


def makeOrthoRandom():

	randRot = [1, 0, 0, 0]
	d = math.pi / 32
	for i in range(3):
		theta = random.uniform(-d, d)
		randRot = SetRotate2(randRot, theta, i)

	direction = Rotation([0, 0, random.randint(5000, 10000)], randRot, [0, 0, 0])

	center = []
	delta = []
	for i in range(3):
		center.append(direction[i])
		delta.append(random.randint(100, 500))

	return [center, delta, makeVertex(center, delta)]

if __name__ == "__main__":
	main()
