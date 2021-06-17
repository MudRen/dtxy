inherit NPC;
void random_leave();
void random_eat();
void create()
{
   set_name("ͺ��", ({ "tu jiu"}) );
   set("race", "Ұ��");
   set("age", 17);
   set("long", "Į��һ�����͵ķ���,�Ը�ʬΪʳ��\n");
   
   set("str", 26);
   set("cor", 24);
   set("combat_exp",80000);

   set("limbs", ({ "ͷ��", "����", "���", "�ҳ�", "���","�ҽ�" }) );
   set("verbs", ({ "bite", "claw" }) );

   set("chat_chance", 6);
   set("chat_msg", ({
  "ͺ������ͷ������,�ƺ���Ѱ�����ֵĻ���.\n",
  "ͺ��������ǰ�治Զ����ʯ��,��������Ķ�ס��.\n",
  (:random_leave:),
  (:random_eat:),
 }));
   set_temp("apply/attack", 20);
   set_temp("apply/armor", 20);

   setup();
}
void init()
{
 object ob;
   ::init();
 if (interactive(ob=this_player())&&!is_fighting()) {
 	remove_call_out("eat_corpse");
 	call_out("eat_corpse",1,ob);
   }
//add_action("do_kill","kill");
add_action("do_kill","hit");
add_action("do_kill","fight");
}
void eat_corpse(object ob)
{
  object corpse;
  corpse=present("corpse",environment());
  if (corpse)  {
 message_vision("$Nһ�����ʳ��$n,ʱ��ʱ����ɢ�ҵ���ë\n",this_object(),corpse);
 return;
}
  return;
}
void random_leave()
{
mapping default_dirs = ([
        "north":                "��",
        "south":                "��",
        "east":                 "��",
        "west":                 "��",
        "northup":              "����",
        "southup":              "�ϱ�",
        "eastup":               "����",
        "westup":               "����",
        "northdown":    "����",
        "southdown":    "�ϱ�",
        "eastdown":             "����",
        "westdown":             "����",
        "northeast":    "����",
        "northwest":    "����",
        "southeast":    "����",
        "southwest":    "����",
        "up":                   "��",
        "down":                 "��",
        "out":                  "��",
]);

        mapping exits;
        string *dirs,*where,dir;
        int i;

    if( !mapp(exits = environment()->query("exits")) ) return;
        dirs = keys(exits);
        where=values(exits);
        i=random(sizeof(dirs));
        
        if( !undefinedp(default_dirs[dirs[i]]) )
                dir = default_dirs[dirs[i]];
        else
                dir =dirs[i];
message_vision("$Nһ������,�����"+dir+"��ȥ.\n",this_object());
       move(where[i]);
tell_room(where[i],"һֻͺ�շ��˹���,�ڿ�������.\n");
return;
}
void do_kill(string arg)
{
  if (!arg||arg!="tu jiu") return;
  random_leave();
  return;
}
void random_eat()
{ object corpse;
  corpse=present("corpse",environment());
  if (corpse)  {
 message_vision("$Nһ�����ʳ��$n,ʱ��ʱ����ɢ�ҵ���ë\n",this_object(),corpse);
 return;
}
return;
}
