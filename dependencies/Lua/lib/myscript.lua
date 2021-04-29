local mapa = {
  { 
    name="ent1",
    id=1,
    components={
      transform={
        position="1,2,3",
        rotation="100,0,100",
        scale="1,1,1"
      },
      renderer={
        mesh="ball.mesh",
        material="red.mat",
        visible="true"
      }--,
      --animation={
      --  animations="Dance,Run",
      --  playing="true",
      --  loop="true"
      --}
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
      camera={
        near="0.1",
        far="1000",
        autoaspect="true",
        aspect="1.78",
        fov="150",
        proyection="0",
        viewport="0,0,500,500",
        color="1.0,0.5,0.3137"
      }--,
      --audiosource={
      --  volume="0.3",
      --  spacial="1"
      --}
    }
  }
}

function GetMapa ()
  return mapa
end

