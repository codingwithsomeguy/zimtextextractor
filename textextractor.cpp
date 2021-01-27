/* Copyright: 2021 Nixiesoft LLC - See LICENSE */

#include <stdio.h>
#include <string.h>

#include <zim/zim.h>
#include <zim/archive.h>
#include <zim/item.h>

#include <lexbor/html/parser.h>
#include <lexbor/html/serialize.h>

#include <vector>
#include <iostream>


static lexbor_action_t walker(lxb_dom_node_t *node, void *ctx) {
    size_t textSize = 0;

    if (node->type == LXB_DOM_NODE_TYPE_TEXT) {
        lxb_char_t *text_content = lxb_dom_node_text_content(node, &textSize);
        std::string s((const char *)text_content, textSize);
        std::cout << s << " ";
    }
    return LEXBOR_ACTION_OK;
}

void extractText(const char *html, size_t size) {
    // std::cout << "extractText: size: " << size << std::endl;

    lxb_html_document_t *doc = lxb_html_document_create();
    if (doc == NULL) {
        exit(EXIT_FAILURE);
    }

    lxb_status_t status = lxb_html_document_parse(
        doc, (const unsigned char *)html, size);
    if (status != LXB_STATUS_OK) {
        printf("extractText: parsing failed\n");
        exit(EXIT_FAILURE);
    }

    lxb_dom_node_t *dom = lxb_dom_interface_node(doc);
    lxb_dom_node_simple_walk(dom, walker, NULL);

    lxb_html_document_destroy(doc);
}

void processEntry(zim::Entry ent) {
    // std::cout << "processEntry: " << ent.getTitle() << std::endl;

    // ignore reidrects for now
    if (!ent.isRedirect()) {
        zim::Item item(ent.getItem());
        // std::cout << "item size: " << item.getSize()
        //     << ", mimetype: " << item.getMimetype() << std::endl;
        if ((strcmp(item.getMimetype().c_str(), "text/html") == 0) ||
                (strcmp(item.getMimetype().c_str(), "text/plain") == 0)) {
            zim::Blob blob(item.getData());
            extractText(blob.data(), item.getSize());
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " ZIMFILE" << std::endl;
        exit(EXIT_FAILURE);
    }

    zim::Archive archive{zim::Archive(argv[1])};
    // std::cout << "processing " << archive.getFilename() << std::endl;

    for (auto& entry : archive.iterEfficient()) {
        processEntry(entry);
    }
    // processEntry(archive.getEntryByTitle("Wiki"));

    return 0;
}
