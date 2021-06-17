// create by snowcat.c 9/18/1998

inherit ROOM;

#define OUTROOM __DIR__"yuwang5"
#define DEATH __DIR__"yuwang6"

void switch_on_off();
int maxi ()
{
  OUTROOM->maxi();
}

int maxj ()
{
  OUTROOM->maxj();
}

void create ()
{
  set ("short", "������");
  set ("long", @LONG

��������������Ũ�����죬��ѬѬ����ʲôҲ�����塡����

LONG);

  set("exits", ([
        "east"   : 0,
        "north"   : 0,
        "south"   : 0,
        "west"   : 0,
      ]));

  set("objects", ([
        __DIR__"npc/yaomo"  : random(2),
      ]));
  
  set("alternative_die",1);
  set("milin",1);
  set("no_look",1);
  if(random(2)==0) switch_on_off();
  setup();
}

void alternative_die(object who)
{
  if (! userp(who) ||
    ! who->query_temp("ymdh/entered")) {
    set("alternative_die",0);
    who->die();
    set("alternative_die",1);
    return;
  }
  DEATH->die(who);
}

int clean_up ()
{
  return 1;
}

void switch_off ()
{
  set ("long", @LONG

��������������Ũ�����죬��ѬѬ����ʲôҲ�����塡����

LONG);

  set("outdoors", 0);
  tell_room (this_object(),"һ��Ũ��Ϯ������ʲô���������ˡ�\n");

}

void switch_on ()
{
  set ("long", @LONG

��������������Ʈ�ŵ�����һ����������ľ������֦Ҷïʢ������

LONG);

  set("outdoors", "milin");
  tell_room (this_object(),"�紵�������������ص��ˡ�\n");

}

void switch_on_off()
{
  int no_look = 1-query("no_look");
  
  if (no_look) {
    if (random(3)) // adjusted off times
      return;
    switch_off();
  } else
    switch_on();
  set("no_look",no_look);
}

void exits_setup ()
{
  object room;
  int i, j;
  mapping exits;
  string *dirs;
  
  i = query("i");
  j = query("j");

  if (query("exits_setup"))
    return;

  room = OUTROOM->search_for_room (i,j+1);
  set("exits/east",room);
  room = OUTROOM->search_for_room (i,j-1);
  set("exits/west",room);
  room = OUTROOM->search_for_room (i-1,j);
  set("exits/north",room);
  room = OUTROOM->search_for_room (i+1,j);
  set("exits/south",room);
  
  exits = query("exits");
  dirs = keys(exits);
  if (this_player() && interactive(this_player()))
    delete("exits/"+dirs[random(sizeof(dirs))]);
  set("exits_setup",1);
  
}

void delaying ()
{
  set("delayed",0);
}

void detecting (object me, int extra)
{
  int d, i, j, k, my_i, my_j;
  object *inv;
  string str, str1, str2;

  if (! me)
    return;
  if (! interactive(me))
    return;
  if (this_object() != environment(me))
    return;
  if (me->is_fighting())
    return;
  
  extra = random(10)+extra;
  if (extra < 600)
    call_out ("detecting",extra,me,extra);

  my_i = this_object()->query("i");
  my_j = this_object()->query("j");
  inv = all_inventory(this_object());
  for(k=0; k<sizeof(inv); k++) {
    if (living(inv[k]) && inv[k]!=me && !me->is_fighting()) {
      tell_object (me, "���ƺ������������ʲô��������\n");
      return;
    }
  }
  for(d=1; d<((maxi()+maxj())/3); d++) {
    for(i=my_i-d; i<=my_i+d; i++) {
      for(j=my_j-d; j<=my_j+d; j++) {
        //reset_eval_cost();
        inv = all_inventory(OUTROOM->search_for_room(i,j));
        for(k=0; k<sizeof(inv); k++) {
          if (living(inv[k]) && inv[k]!=me) {
	    str = "��·����";
	    if (j < my_j)
		str += "��";
	    else if (j > my_j)
		str += "��";
	    if (i < my_i)
		str += "��";
	    else if (i > my_i)
		str += "��";
	    str += "��";
            if (d <= (maxi()+maxj())/9)
		str += "����";
	    else if (d <= (maxi()+maxj())*2/9)
		str += "��Զ��";
	    else
		str += "Զ��";
            tell_object (me, str+"��ʲô�������������ıƽ�����\n");
            return;
          }
        }
      }
    }
  }
}

void init ()
{
  object who = this_player();
  object *usr;
  int i;

  // mon
  add_action("do_cast","cast");
  add_action("do_quit","quit");

  if (who && interactive(who)) {
    set("delayed",1);
    call_out ("exits_setup",1);
    call_out ("delaying",1);
    call_out ("detecting",1,this_player(),5);
    
    // mon 9/26/98 auto attacking others.
    if(random(10)>0) return;

    usr=all_inventory(this_object());
    i=sizeof(usr);
    while(i--) {
	if(!userp(usr[i])) continue;
	if(who==usr[i]) continue;
	who->kill_ob(usr[i]);
	usr[i]->kill_ob(who);
    }
  }
}

int do_quit(string arg)
{
    return 1;
}

int do_cast(string arg)
{
    if(!arg) return 0;

    while(sscanf(arg,"%s %*s",arg)==2);

    if(arg!="qiankun") return 0;
    
    write("��������֦Ҷïʢ����Ĵ���ʵ����ʩչ��������\n");
    return 1;
}

void trapped ()
{
  object *inv;
  int k;

  inv = all_inventory(this_object());
  for(k=0; k<sizeof(inv); k++) {
    if (interactive(inv[k])) {
      message_vision ("һ������Ϯ����$N��һ�ᱻ����ؾ����ˡ�\n",inv[k]);
      inv[k]->move(OUTROOM->random_room());
      message_vision ("$N��һ��Ũ�ҵ��������˹�����\n",inv[k]);
      return;
    }
  }
}

int valid_leave (object who, string dir)
{
  if (! interactive(who)) 
    return ::valid_leave(who, dir);
  if (!query("exits_setup") || query("delayed"))
    return notify_fail ("����Ũ����������һͷײ�˸��ա�\n");
  set("exits_setup",0);
  exits_setup();
  return ::valid_leave(who, dir);
}



