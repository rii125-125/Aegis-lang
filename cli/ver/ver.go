package ver

import (
	"io/ioutil"
)

var Ver string = ver()

func ver() string {
	file := "lasted_version.txt"

	text, err := ioutil.ReadFile(file)
	if err != nil {
		err.Error()
	}

	return string(text)
}