import express from 'express'
import fs from 'fs'
import ResponseBuilder from './responseBuilder'
import yargs, { strict } from 'yargs'
import { hideBin } from 'yargs/helpers'



const argv = yargs(hideBin(process.argv))
    .option('file', {
        alias: 'f',
        type: 'string',
        description: 'Path to settings file'
    })
    .parse() as any


const settings_file: string = argv.f || './settings.json'

var options = JSON.parse(fs.readFileSync(settings_file).toString())

fs.watchFile(settings_file, { interval: 1000 }, (_curr, _prev) => {
    options = JSON.parse(fs.readFileSync(settings_file).toString())
})

const app = express()
app.use('/', (req: express.Request, res: express.Response) => {
    const rb = new ResponseBuilder(options.hosts, req)
    rb.end(res)
})

app.listen(80, () => {
    console.log('Server start!')
})




