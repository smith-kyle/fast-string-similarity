{
    "targets": [
        {
            "target_name": "FastStringCompare",
            "sources": ["FastStringCompare.cc", "functions.cc"],
            "include_dirs": ["<!(node -e \"require('nan')\")"],
        }
    ],
}
