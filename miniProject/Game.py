import pygame
from pygame.locals import *
import random
# initialize the game
pygame.init()

clock = pygame.time.Clock()
fps =60
#game variables
screen_width = 864
screen_height = 768
flying = False
game_over =False
pipe_gap =250
pipe_frequency = 1500 #miliseconds 
last_pipe =pygame.time.get_ticks() - pipe_frequency # substraction is done to not to wait 1500 miliseconds for 1st pipe to come
score = 0
pass_pipe = False


# game window dimensions
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Flappy Bird")

#load image background
bg = pygame.image.load('img/bg.png')
ground_img = pygame.image.load('img/ground.png')
button_img = pygame.image.load('img/restart.png')
#define font
font = pygame.font.SysFont("Bauhaus 93", 60)
#define color
white = (255,255,255)
#
def draw_text(text, font, text_col, x, y):
    img = font.render(text, True, text_col)
    screen.blit(img, (x, y))
    
def reset_game():
    pipe_group.empty()
    flappy.rect.x = 100
    flappy.rect.y = int(screen_height/2)
    score =0
    return score

    
class Button():
    def __init__(self,x,y,image):
        self.image = image
        self.rect = self.image.get_rect()
        self.rect.topleft = (x,y)
        
    def draw(self):
        action = False
        #get mouse position
        pos = pygame.mouse.get_pos()
        
        #check mouse is over the button
        if self.rect.collidepoint(pos):
            if pygame.mouse.get_pressed()[0] == 1:
                action = True
        
        screen.blit(self.image, (self.rect.x, self.rect.y))
        
        return action
        
        
        
class Bird(pygame.sprite.Sprite):
    def __init__(self, x ,y):
        pygame.sprite.Sprite.__init__(self)
        self.images = [] #list of images
        self.index = 0  #selecting img index
        self.counter = 0
        for num in range (1,4):
            img = pygame.image.load(f'img/bird{num}.png')
            self.images.append(img)
        self.image = self.images[self.index]
        self.rect = self.image.get_rect()
        self.rect.center = [x,y]
        self.vel = 0 #velocity of bird in upward/downward direction
        self.clicked = False #to control the mouse click
    
    # overwrite update function of sprite
    def update(self):
        
        if flying == True:
            self.vel += 0.5
            # print(self.vel)
            # to stop and the incresing velocity
            if(self.vel > 8):
                self.vel = 8
            #bird going downward direction
            if self.rect.bottom < 668:
                self.rect.y += int(self.vel)  
        if game_over == False:    
            if (pygame.mouse.get_pressed()[0] == 1 or pygame.key.get_pressed()[K_SPACE]==1) and self.clicked == False:
                self.clicked = True
                self.vel = -10
                sound = pygame.mixer.Sound('sound/sfx_wing.wav')
                sound.play()
            if pygame.mouse.get_pressed()[0] == 0 or pygame.key.get_pressed()[K_SPACE] ==0:
                self.clicked = False
         
            
            # handle the animation
            self.counter += 1
            flap_cooldown = 5
        
            if self.counter > flap_cooldown:
                self.counter = 0
                self.index += 1
                if(self.index >= len(self.images)):
                    self.index = 0
            self.image = self.images[self.index]   
            
            # rotate the bird
            self.image = pygame.transform.rotate(self.images[self.index], self.vel * -2)
        else:
            self.image = pygame.transform.rotate(self.images[self.index], -90) # second parameter is angle

class Pipe(pygame.sprite.Sprite):
    def __init__(self,x,y,position):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load('img/pipe.png')
        self.rect = self.image.get_rect()
        if position == 1:
            self.image = pygame.transform.flip(self.image, False, True)
            self.rect.bottomleft =[x,y - int(pipe_gap/2)]
        if position == -1:
            self.rect.topleft = [x,y + int(pipe_gap/2)] 
            
    
    def update(self):
        self.rect.x -= scroll_speed
        if self.rect.right < 0:
            self.kill()  #to save memory pipes after going offscreen
        
bird_group = pygame.sprite.Group()
pipe_group = pygame.sprite.Group()

flappy = Bird(100, int(screen_height/2))

bird_group.add(flappy)



#game variables
ground_scroll =0 # x variable of ground image
scroll_speed = 4  #speed at which ground will move

#restart button
button = Button(screen_width // 2 - 50, screen_height // 2 - 100, button_img)

run = True
while run:
    
    clock.tick(fps)
    
    # draw background
    screen.blit(bg, (0,0))
    
    # to draw a bird
    bird_group.draw(screen)  
    
    # to make animation of bird 
    bird_group.update()
    
    
    pipe_group.draw(screen)
    
    
    #stationary ground draw
    screen.blit(ground_img, (ground_scroll,668))
    
    # check the score
    if len(pipe_group) > 0:
        if bird_group.sprites()[0].rect.left > pipe_group.sprites()[0].rect.left\
            and bird_group.sprites()[0].rect.right < pipe_group.sprites()[0].rect.right\
                and pass_pipe == False:
                    pass_pipe = True

        if pass_pipe == True:
            if bird_group.sprites()[0].rect.left > pipe_group.sprites()[0].rect.right:
                score += 1
                pass_pipe = False
                sound = pygame.mixer.Sound('sound/sfx_point.wav')
                sound.play()
    
    draw_text(str(score), font, white, int(screen_width/2), 20)
            
    #look for collision
    if pygame.sprite.groupcollide(bird_group, pipe_group, False, False) or flappy.rect.top < 0:
        game_over =True
        
    #check if bird is hit the ground
    if flappy.rect.bottom >= 668:
        game_over =True
        flying = False
        
    if game_over ==False and flying == True:
        #generate new pipes
        time_now = pygame.time.get_ticks()
        if time_now - last_pipe > pipe_frequency:
            pipe_height = random.randint(-100, 100)
            btm_pipe = Pipe(screen_width, int(screen_height/2) + pipe_height,-1)
            top_pipe = Pipe(screen_width, int(screen_height/2) + pipe_height,1)
            pipe_group.add(btm_pipe)
            pipe_group.add(top_pipe)
            last_pipe = time_now
        # scroll ground_img
        ground_scroll -= scroll_speed
        if abs(ground_scroll) > 35:  #extra ground image going back to 0 x variable  Also ground_scroll will become negative so abs is used
            ground_scroll = 0
            
        pipe_group.update()
    playsound=False
    #check for gameover and reset
    if game_over == True:
        draw_text("GAME OVER", font,(255,0,0),int(screen_width/2)-120,150)
        
        if button.draw() == True:
            game_over =False
            score = reset_game()
           
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  #if close button is press game gets close
            run = False
            
        if (event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.KEYDOWN) and flying==False and game_over==False:
            if event.type == pygame.MOUSEBUTTONDOWN or event.key == pygame.K_SPACE:
                flying = True
    
    pygame.display.update()
pygame.quit()  