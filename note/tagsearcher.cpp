#include "tagsearcher.h"

#include <QSqlQuery>
#include <QSet>
#include <QVariant>
#include <QDebug>

TagSearcher::TagSearcher()
{}

TagSearcher::TagSearcher(Tag::List tags, QSqlDatabase db):
        tags(tags),
        database(db)
{}

QSet<int> TagSearcher::getAllNotes() {
    QSqlQuery query(database);

    QSet<int> notesId;

    bool firstTime = true;

    query.prepare("select distinct note_id from note_tag where tag_id = :tag_id AND tag_state = :tag_state AND tag_param = :tag_param");

    foreach(Tag tag, tags) {
        query.bindValue(":tag_id", tag.getId());
        query.bindValue(":tag_state", tag.getState());
        query.bindValue(":tag_param", tag.getParam());
        query.exec();

        QSet<int> ids;

        while(query.next()) {
            int noteId = query.value(0).toInt();
            if (! ids.contains(noteId)) {
                ids << noteId;
            }
        }

        if (firstTime) {
            notesId.unite(ids);
            firstTime = false;
        } else {
            notesId.intersect(ids);
        }
    }

    return notesId;
}

