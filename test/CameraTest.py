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

	pos = [0, 0, 100]
	rot = [1, 0, 0, 0]
	r = 30
	dRot = 0.002

	isRoop = True

	while(isRoop):

		# 回転の反映
		newpos = Rotation([1, pos[0], pos[1], pos[2]], rot)

		# 座標の計算
		x = distance * newpos[0] / (distance + newpos[2]) + 640
		y = distance * newpos[1] / (distance + newpos[2]) * -1 + 360

		# 描画
		screen.fill((0, 0, 0))
		pygame.draw.circle(screen, (255, 255, 255), (x, y), r)

		txt = ""
		for i in range(4):
			txt += "{:.4f}, ".format(rot[i])
		screen.blit(font.render(txt, False, (255, 255, 255)), (0, 720-64))
		pygame.display.flip()


		# キー入力
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				isRoop = False
		keys = pygame.key.get_pressed()		
		if keys[pygame.K_KP2]:
			rot = SetRotate(rot, dRot, 0)
		if keys[pygame.K_KP8]:
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
