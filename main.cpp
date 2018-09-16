#include <QCoreApplication>

#include "dumpjob.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    new DumpJob("TechnoBase.FM",  "lw1.mp3.tb-group.fm",   80,   "/tb.mp3");
    new DumpJob("HouseTime.FM",   "lw1.mp3.tb-group.fm",   80,   "/ht.mp3");
    new DumpJob("HardBase.FM",    "lw1.mp3.tb-group.fm",   80,   "/hb.mp3");
    new DumpJob("TranceBase.FM",  "lw1.mp3.tb-group.fm",   80,   "/trb.mp3");
    new DumpJob("CoreTime.FM",    "lw1.mp3.tb-group.fm",   80,   "/ct.mp3");
    new DumpJob("ClubTime.FM",    "lw1.mp3.tb-group.fm",   80,   "/clt.mp3");
    new DumpJob("TeaTime.FM",     "lw1.mp3.tb-group.fm",   80,   "/tt.mp3");
    new DumpJob("Trap.FM",        "stream.trap.fm",        6002, "/");
    new DumpJob("Dubbase.FM",     "stream.dubbase.fm",     7002, "/");
    new DumpJob("DrumAndBass.FM", "stream.drumandbass.fm", 9002, "/");

    return app.exec();
}
