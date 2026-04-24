using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vectora;

namespace Sandbox
{
    public class Player : Entity
    {
        void OnCreate()
        {
            Console.WriteLine($"Player.Oncreate- id {ID}");
        }

        void OnUpdate(float ts)
        {
            Console.WriteLine($"Player on update: {ts}");
            float speed = 1.0f;

            Vector3 translation = this.Translation;
            translation.X += speed * ts;
            this.Translation = translation;
        }

        // had to add this so visual studio don't gray out the methods above, since they are called from native code
        void do_nothing()
        {
            OnCreate();
            OnUpdate(0.1f);
        }
    }
}
