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
	font = pygame.font.SysFont(None, 64)
	time.sleep(1)


	# テスト
	# https://mitani.cs.tsukuba.ac.jp/lecture/old2015/cg/03/03_slides.pdf
	fov = math.pi / 4
	distance = 640 / math.tan(fov / 2)

	rot = [1, 0, 0, 0]
	dRot = 0.001

	opos = [100, 100, 1000]
	size = 200
	p = [
		[opos[0],      opos[1],      opos[2]],
		[opos[0]-size, opos[1],      opos[2]],
		[opos[0]-size, opos[1]-size, opos[2]],
		[opos[0],      opos[1]-size, opos[2]],
		[opos[0],      opos[1],      opos[2]],
		[opos[0],      opos[1],      opos[2]+size],
		[opos[0],      opos[1]-size, opos[2]+size],
		[opos[0],      opos[1]-size, opos[2]],
		[opos[0],      opos[1],      opos[2]],
		[opos[0],      opos[1],      opos[2]+size],
		[opos[0]-size, opos[1],      opos[2]+size],
		[opos[0]-size, opos[1],      opos[2]],

	]

	isRoop = True
	while(isRoop):

		# 回転
		q = []
		for xyz in p:
			q2 = Rotation([1, xyz[0], xyz[1], xyz[2]], rot)
			q.append(q2)

		vertex = []
		isDraw = True

		# 座標の計算
		for xyz in q:
			if xyz[2] > -distance:
				x = distance * xyz[0] / (distance + xyz[2]) + 640
				y = distance * xyz[1] / (distance + xyz[2]) * -1 + 360
				vertex.append([x, y])
			else:
				isDraw = False

		# 描画
		screen.fill((0, 0, 0))
		if isDraw: pygame.draw.polygon(screen, (255, 255, 255), vertex, width=5)
		pygame.display.flip()


		# キー入力
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				isRoop = False
		keys = pygame.key.get_pressed()		
		if keys[pygame.K_KP8]:
			rot = SetRotate(rot, dRot, 0)
		if keys[pygame.K_KP2]:
			rot = SetRotate(rot, -dRot, 0)
		if keys[pygame.K_KP4]:
			rot = SetRotate(rot, dRot, 1)
		if keys[pygame.K_KP6]:
			rot = SetRotate(rot, -dRot, 1)
		if keys[pygame.K_KP9]:
			rot = SetRotate(rot, dRot, 2)
		if keys[pygame.K_KP7]:
			rot = SetRotate(rot, -dRot, 2)
		if keys[pygame.K_KP5]:
			rot = [1, 0, 0, 0]
		if keys[pygame.K_ESCAPE]:
			pygame.quit()
			isRoop = False				
	return

def Rotation(pos: list, rot: list):

	newList = calc(rot, pos)
	rotConjugate = [rot[0], -rot[1], -rot[2], -rot[3]]
	newList = calc(newList, rotConjugate)

	return newList[1:]

def SetRotate(before: list, delta: float, n: int):
	r = [math.cos(delta), 0, 0, 0]
	r[n+1] = math.sin(delta)

	return calc(r, before)


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

if __name__ == "__main__":
	main()
