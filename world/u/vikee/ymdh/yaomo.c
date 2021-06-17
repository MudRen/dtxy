// created by snowcat on 12/9/1997
// modified by vikee for dtxy 2000.11

inherit NPC;

string *names1 = ({
  "̡",
  "¹",
  "�",
  "��",
  "��",
  "��",
  "��",
  "��",
});

string *names2 = ({
  "ͷ",
  "β",
  "��",
  "צ",
  "��",
  "��",
});

string *names3 = ({
  "��",
  "ʨ",
  "��",
  "��",
  "�",
  "��",
  "��",
  "��",
});

int eff_dx;
int already_setup=0;

int random_action();
void set_data();

void create()
{

  string str;
  str = names1[random(sizeof(names1))]+names2[random(sizeof(names2))]+names3[random(sizeof(names3))];
  set_name(str, ({"yao mo", "yao", "mo"}));
  set("gender", "����");
  set("attitude", "aggressive");
  set("chat_chance", 10);
  set("chat_msg", ({
      (: random_action :)
   }));

  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  already_setup=0;
}

void init()
{
    if(!already_setup)
        set_data();
    ::init();
}

void set_data()
{
  string long;
  int i,k,m;
  int j, dx, year;
  object env=environment(this_object());

  if(!env) return;
  year=env->query("year");
  if(!year) return;
  
  already_setup=1;
  k=year/10;
  m=11*year/10;
  i=k+random((m-k)/10+1)*10;
  if(i>10000) i=10000;

  set("age", i*2);
  dx=1000*i;
  set("combat_exp", dx);
  
  for(j=7;j<50;j=j+2)
      if(j*j*j/10>i) break;

  j=j*5;

  set("per", 10);
  set_skill("parry", j);
  set_skill("unarmed", j);
  set_skill("dodge", j);
  set_skill("blade", j);
  set_skill("fork", j);
  set_skill("mace", j);
  set_skill("spear", j);
  set_skill("sword", j);
  set_skill("whip", j);
  set_skill("axe", j);
  set_skill("hammer", j);
  set_skill("rake", j);
  set_skill("stick", j);
  set_skill("staff", j);
  set_skill("dagger", j);
  
  j=j/2+1;
  set("max_sen",10*j);
  set("max_kee",10*j);
  set("max_gin",10*j);
  set("eff_sen",10*j);
  set("eff_kee",10*j);
  set("eff_gin",10*j);
  set("sen",10*j);
  set("kee",10*j);
  set("gin",10*j);
  set("force",10*j);
  set("max_force",10*j);
  set("max_mana",10*j);
  set("mana",10*j);
  set("force_factor",j/2);

  // mon 9/25/98
  j=(random(2)==0)?1:-1;
  long="һͷ"+name()+"����������"+
      chinese_number((dx/1000/10)*10)+
       "������С���";
  if(j==1) {
      set("long",long+"ͨ��͸��һ˿������\n");
  } else {
      set("long",long+"���������������ˡ�\n");
  }

}

int random_action()
{
  object env = environment(this_object());
  object *obs;
  int i, exp;

  if (! is_fighting() &&
      living(this_object()) &&
      env) {
    random_move();
    env = environment(this_object()); // notice: new env
    obs = all_inventory(env);
    i = sizeof(obs);
    while (i--) {
        // mon 9/26/98
        exp=obs[i]->query("combat_exp");

      if (userp(obs[i]) && eff_dx>exp) {
        kill_ob(obs[i]);
      }
    }
  }
  return 0;
}

varargs int move (mixed dest, int silently)
{
  int i = ::move (dest, silently);
      
  init();
  return i;
}

void die()
{
    object killer = this_object()->query_temp("last_damage_from");
        object ye;
        message("vision",this_object()->query("name")+ "���ˡ�\n\n", environment());  
        tell_object(killer,"�����һ������С�\n");
        killer->add("counter",1);                          
        ye=new("/d/kaifeng/npc/ye.c");
        ye->command_function("sldh "+killer->query("name")+"ɱ����" + this_object()->query("name")+"���õ���һ������У�\n");
    killer->add("daoxing",400);
        destruct(ye);
        destruct(this_object());


}


