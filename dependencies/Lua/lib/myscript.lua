    local mapa = {
      {
        name="ent1",
        id=1,
        components={
          transform={
            pos="1,2,3",
            rot="100,0,100",
            scale="1,1,1"
          },
          renderer={
            mesh="ball.mesh",
            material="red.mat"
          }
        }
      },
      {
        name="ent2",
        id=2,
        components={
          transform={
            pos="1,2,3",
            rot="100,0,100",
            scale="1,1,1"
          },
          audiosource={
            volume="0.3",
            spacial="1"
          }
        }
      }
    }

    function GetMapa ()
      return mapa
    end