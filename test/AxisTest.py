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

	rot = [0, 0, 0]
	dRot = [0.005, 0.005, 0.005]

	length = 200
	xAxis = [length, 0, 0, 1]
	yAxis = [0, length, 0, 1]
	zAxis = [0, 0, -length, 1]

	isRoop = True
	while(isRoop):

		# 回転
		xyz = [
			Rotation(xAxis, rot),
			Rotation(yAxis, rot),
			Rotation(zAxis, rot)
		]
		vertex = [[], [], []]
		isDraw = [True, True, True]

		# 座標の計算
		for i in range(3):
			if xyz[i][2] > -distance:
				x = distance * xyz[i][0] / (distance + xyz[i][2]) + 640
				y = distance * xyz[i][1] / (distance + xyz[i][2]) * -1 + 360
				vertex[i].append(x)
				vertex[i].append(y)
			else:
				isDraw[i] = False

		# 描画
		color = [
			(0, 0, 255),
			(0, 255, 0),
			(255, 0, 0 )
		]
		screen.fill((0, 0, 0))
		for i in range(3):
			if isDraw[i]:
				start = (640, 360)
				end = (vertex[i][0], vertex[i][1])
				pygame.draw.line(screen, color[i], start, end, width=5)

		deg = round(rot[0] * 180 / math.pi)
		txt = font.render("Roll: " + str(deg), False, (255, 255, 255))
		screen.blit(txt, (0, 720-64*3))
		deg = round(rot[1] * 180 / math.pi)
		txt = font.render("Pitch: " + str(deg), False, (255, 255, 255))
		screen.blit(txt, (0, 720-64*2))
		deg = round(rot[2] * 180 / math.pi)
		txt = font.render("Yaw: " + str(deg), False, (255, 255, 255))
		screen.blit(txt, (0, 720-64*1))

		pygame.display.flip()


		# キー入力
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				isRoop = False
		keys = pygame.key.get_pressed()		
		if keys[pygame.K_KP9]:
			rot[0] += dRot[0]
		if keys[pygame.K_KP7]:
			rot[0] -= dRot[0]
		if keys[pygame.K_KP8]:
			rot[1] -= dRot[1]
		if keys[pygame.K_KP2]:
			rot[1] += dRot[1]
		if keys[pygame.K_KP6]:
			rot[2] += dRot[2]
		if keys[pygame.K_KP4]:
			rot[2] -= dRot[2]
		if keys[pygame.K_KP5]:
			rot = [0, 0, 0]
		if keys[pygame.K_ESCAPE]:
			pygame.quit()
			isRoop = False				
	return

def Rotation(a: list, b: list):

	newList = []

	mPlayer = [a[3], a[0], a[1], a[2]]
	mPlayerConjugate = [a[3], -a[0], -a[1], -a[2]]
	mRotRoll  = [math.cos(b[0]/2),                0,                0, math.sin(b[0]/2)]
	mRotPitch = [math.cos(b[1]/2), math.sin(b[1]/2),                0,                0]
	mRotYaw   = [math.cos(b[2]/2),                0, math.sin(b[2]/2),                0]
	mRotRollConjugate  = [math.cos(b[0]/2),                 0,                 0, -math.sin(b[0]/2)]
	mRotPitchConjugate = [math.cos(b[1]/2), -math.sin(b[1]/2),                 0,                 0]
	mRotYawConjugate   = [math.cos(b[2]/2),                 0, -math.sin(b[2]/2),                 0]

	newList = calc(makeMatrix(mRotYaw), mPlayer)
	newList = calc(makeMatrix(newList), mRotYawConjugate)
	newList = calc(makeMatrix(mRotPitch), newList)
	newList = calc(makeMatrix(newList), mRotPitchConjugate)
	newList = calc(makeMatrix(mRotRoll), newList)
	newList = calc(makeMatrix(newList), mRotRollConjugate)

	return [newList[1], newList[2], newList[3], newList[0]]


def calc(f:list, b:list):

	newList = []

	for i in range(4):
		s = 0
		for j in range(4):
			s += f[i][j] * b[j]
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
