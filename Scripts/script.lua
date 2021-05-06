entities = {
  count = 1,
  array = {
    {
      physics = {
        x = 10, 
        y = 10,
        speed = 0.4,
        size = 64
      },
      graphics = {
        path = "../Resources/hero.png"
      },
      combat = {
        health = 100,
        attack = 10,
        defense = 5,
        cooldown = 100
      }
    }
  }
}

map = {
  version = "1.5",
  luaversion = "5.1",
  tiledversion = "1.6.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 14,
  height = 15,
  tilewidth = 16,
  tileheight = 16,
  nextlayerid = 2,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "ChromaDungeon",
      firstgid = 1,
      filename = "ChromaDungeon.tsx"
    }
  },
  layers = {
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 14,
      height = 15,
      id = 1,
      name = "Tile Layer 1",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4,
        8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10,
        8, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 10,
        8, 11, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10,
        8, 11, 6, 6, 12, 21, 21, 21, 21, 18, 6, 6, 6, 10,
        8, 11, 6, 6, 10, 2, 3, 3, 4, 8, 11, 6, 6, 10,
        8, 11, 6, 6, 10, 8, 9, 9, 10, 8, 11, 6, 6, 10,
        8, 11, 6, 6, 10, 8, 5, 15, 10, 8, 11, 6, 6, 10,
        8, 11, 6, 6, 10, 8, 11, 6, 10, 8, 11, 6, 6, 10,
        8, 11, 6, 6, 24, 30, 11, 6, 24, 30, 11, 6, 6, 10,
        8, 11, 6, 6, 9, 9, 11, 6, 9, 9, 11, 6, 6, 10,
        8, 11, 6, 6, 15, 15, 17, 6, 15, 15, 17, 6, 6, 10,
        8, 11, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10,
        8, 11, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10,
        20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22
      }
    }
  }
}
